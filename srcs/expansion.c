/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:43:13 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/06 01:30:36 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	value_len(char *var, int *i)
{
	int		j;
	char	*tmp;
	t_env	*tmp_env;

	j = 0;
	while (ft_isalnum(var[*i + j]))
		j++;
	tmp = ft_strndup(var + *i, j);
	if (!tmp)
		return (ft_perror("minishell", NULL, 0));
	(*i) += j;
	tmp_env = g_data.env_lst;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->var, tmp))
			break ;
		tmp_env = tmp_env->next;
	}
	j = -1;
	if (tmp_env)
		j += ft_strlen(tmp_env->value);
	j -= ft_strlen(tmp);
	free(tmp);
	return (j);
}

int	get_expansion_len(char *var, int *i, int *is_expand)
{
	int	len;

	len = 0;
	if (var[*i] == '?')
	{
		len++;
		(*i)++;
		*is_expand = 1;
	}
	else if (ft_isalpha(var[*i]))
	{
		len += value_len(var, i);
		*is_expand = 1;
	}
	else
		(*i)++;
	return (len);
}

int	len_after_expand(char *value)
{
	int	len;
	int	i;
	int	is_expand;

	len = ft_strlen(value);
	i = 0;
	is_expand = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			mv_2_nxt_quote(value, &i);
		else if (value[i] == '\"')
		{
			i++;
			while (value[i] != '\"')
				if (value[i++] == '$')
					len += get_expansion_len(value, &i, &is_expand);
		}
		else if (value[i++] == '$')
			len += get_expansion_len(value, &i, &is_expand);
	}
	if (!is_expand)
		return (-1);
	return (len);
}

void	get_expanded_val(char *value, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			while (value[++i] != '\'')
				new[j++] = value[i];
			i++;
		}
		else if (value[i] == '\"')
		{
			i++;
			while (value[i] != '\"')
				check_n_expand(value, new, &i, &j);
			i++;
		}
		else
			check_n_expand(value, new, &i, &j);
	}
	new[j] = 0;
}

int	ft_expand(t_token *token)
{
	int		len;
	char	*new;

	while (token)
	{
		if (token->type != HRDOC && token->type != PIPE)
		{
			len = len_after_expand(token->value);
			if (len < 0)
			{
				token = token->next;
				continue ;
			}
			new = ft_malloc(len + 1, 1, 0);
			if (!new)
				return (-1);
			get_expanded_val(token->value, new);
			free(token->value);
			token->value = new;
		}
		token = token->next;
	}
	return (0);
}
