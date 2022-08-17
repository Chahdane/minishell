/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:13:07 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/17 01:51:15 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unset_naming(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		g_data.exit_code = 1;
		return (-1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", str);
			g_data.exit_code = 1;
			return (-1);
		}
		i++;
	}
	return (1);
}

void	delete_node(t_env **head, t_env *env, t_env *prev)
{
	t_env	*tmp;

	if (prev == env)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		return ;
	}
	tmp = env;
	prev->next = env->next;
	free(tmp->var);
	free(tmp->value);
	free(tmp);
}

void	search_and_unset(char *str)
{
	t_env	*env;
	t_env	*temp;
	t_env	*prev;

	env = g_data.env_lst;
	temp = env;
	prev = env;
	while (env)
	{
		if (ft_strcmp(env->var, str) == 0)
		{
			delete_node(&g_data.env_lst, env, prev);
			break ;
		}
		prev = env;
		env = env->next;
	}
}

void	unset(t_cmd	*cmd)
{
	t_env	*env;
	char	**args;
	int		i;

	i = 0;
	env = g_data.env_lst;
	g_data.exit_code = 0;
	args = cmd->args + 1;
	if (!*args)
		return ;
	while (args[i])
	{
		if (check_unset_naming(args[i]) == 1)
			search_and_unset(args[i]);
		i++;
	}
	fill_env();
}
