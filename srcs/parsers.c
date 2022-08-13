/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/13 16:01:01 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new;

	new = ft_malloc(1, sizeof(t_cmd), 0);
	if (!new)
		return (NULL);
	new->infiles = NULL;
	new->outfiles = NULL;
	new->heredoc_lst = NULL;
	new->heredoc_path = NULL;
	new->heredoc = -1;
	new->input_source = STDIN;
	new->args_lst = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

int	clear_cmds_lst(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		clear_names_lst(cmds->infiles);
		clear_names_lst(cmds->outfiles);
		clear_names_lst(cmds->heredoc_lst);
		clear_names_lst(cmds->args_lst);
		if (cmds->heredoc_path)
			unlink(cmds->heredoc_path);
		free(cmds->heredoc_path);
		free(cmds->args);
		if (cmds->heredoc > 0)
			close(cmds->heredoc);
		free(cmds);
		cmds = tmp;
	}
	g_data.cmds = NULL;
	return (-1);
}

int	fill_in_cmds(t_token *token, t_cmd *new)
{
	if (token->type == INF)
	{
		new->input_source = INFILE;
		if (add_name(&new->infiles, token))
			return (-1);
	}
	else if (token->type == OUTF || token->type == APPF)
	{
		if (add_name(&new->outfiles, token))
			return (-1);
	}
	else if (token->type == HRDOC)
	{
		new->input_source = HEREDOC;
		if (add_name(&new->heredoc_lst, token))
			return (-1);
	}
	else if (token->type == OTHER)
	{
		if (add_name(&new->args_lst, token))
			return (-1);
	}
	return (0);
}

int	transform_tokens(t_token *tokens)
{
	t_cmd	*new;

	g_data.cmds = create_new_cmd();
	if (!g_data.cmds)
		return (-1);
	new = g_data.cmds;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			new->next = create_new_cmd();
			if (!new->next)
				return (clear_cmds_lst(g_data.cmds));
			new = new->next;
		}
		else if (fill_in_cmds(tokens, new))
			return (clear_cmds_lst(g_data.cmds));
		tokens = tokens->next;
	}
	new = g_data.cmds;
	while (new)
		if (args_lst_to_arr(&new))
			return (clear_cmds_lst(g_data.cmds));
	return (0);
}

void	print_cmds(void)
{
	t_cmd	*cmd;
	t_name	*tmp;
	char	*tmp_cmd = NULL;
	int		i;

	cmd = g_data.cmds;
	printf("\n");
	while (cmd)
	{
		if (cmd->args)
			tmp_cmd = (cmd->args)[0];
		printf("\e[0;31mCMD = (%s)\e[0;37m\n", tmp_cmd);
		tmp = cmd->infiles;
		printf("\e[0;32mINFILES = \e[0;37m");
		while (tmp)
		{
			printf("(%s)", tmp->name);
			tmp = tmp->next;
			if (tmp)
				printf(", ");
		}
		printf("\n");
		tmp = cmd->outfiles;
		printf("\e[0;33mOUTFILES = \e[0;37m");
		while (tmp)
		{
			printf("(%s) ==> ", tmp->name);
			printf("%s", tmp->out_mode == NEW ? "new" : "append");
			tmp = tmp->next;
			if (tmp)
				printf(", ");
		}
		printf("\n");
		tmp = cmd->heredoc_lst;
		printf("\e[0;34mHEREDOCS = \e[0;37m");
		while (tmp)
		{
			printf("(%s)", tmp->name);
			tmp = tmp->next;
			if (tmp)
				printf(", ");
		}
		printf("\n");
		if (cmd->input_source == STDIN)
			printf("\e[0;36mINPUT_SOURCE = standard input\e[0;37m\n");
		else if (cmd->input_source == HEREDOC)
			printf("\e[0;36mINPUT_SOURCE = heredoc\e[0;37m\n");
		else if (cmd->input_source == INFILE)
			printf("\e[0;36mINPUT_SOURCE = infile\e[0;37m\n");
		tmp = cmd->args_lst;
		printf("\e[1;32mARGS_LIST = \e[0;37m");
		while (tmp)
		{
			printf("(%s)", tmp->name);
			tmp = tmp->next;
			if (tmp)
				printf(" -> ");
		}
		printf("\n");
		printf("\e[1;31mARGS_ARRAY = \e[0;37m");
		i = 0;
		while (cmd->args && (cmd->args)[i])
		{
			printf("[%i] == (%s)", i, (cmd->args)[i]);
			i++;
			if ((cmd->args)[i])
				printf(", ");
		}
		cmd = cmd->next;
		if (cmd)
			printf("\n\n     =======================      \n\n");
		else
			printf("\n");
	}
}

void	print_heredocs(void)
{
	t_cmd	*tmp;
	char	*line;
	int		i;

	tmp = g_data.cmds;
	i = 0;
	printf("\n");
	while (tmp)
	{
		if (tmp->heredoc == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		line = get_next_line(tmp->heredoc);
		printf("heredoc number %i\n", i++);
		while (line)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(tmp->heredoc);
		}
		printf("\n\n======================\n\n");
		tmp = tmp->next;
	}
}

int	parse_line(char *line)
{
	t_token	*tokens;

	if (check_quotes(line))
		return (-1);
	tokens = make_token_lst(line);
	if (!tokens || ft_expand(tokens))
		return (clear_token_lst(tokens) == NULL);
	if (transform_tokens(tokens))
		return (clear_token_lst(tokens) == NULL);
	if (read_heredocs())
		return (clear_token_lst(tokens) == NULL);
	//print_cmds();
	//print_heredocs();
	clear_token_lst(tokens);
	return (0);
}
