/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:43:13 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/04 16:18:48 by owahdani         ###   ########.fr       */
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

int	get_expansion_len(char *var, int *i)
{
	int	len;

	len = 0;
	if (value[*i] == '?')
	{
		len++;
		(*i)++;
	}
	else if (is_alpha(value[*i]))
		len += value_len(value, i);
	else
		(*i)++;
	return (len);
}

int	len_after_expand(char *value)
{
	int	len;
	int	i;

	len = ft_strlen(value);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			mv_2_nxt_quote(value, &i)
		else if (value[i] == '\"')
		{
			i++;
			while (value[i] != '\"')
			{
				if (value[i++] == '$')
					len += get_expansion_len(value, &i);
			}
		}
		else if (value[i++] == '$')
			len += get_expansion_len(value, &i);
	}
	return (len);
}

int	ft_expand(t_token *token)
{
	int		len;
	char	*tmp;

	while (token)
	{
		if (token->type != HRDOC && token->type != PIPE)
		{
			len = len_after_expand(token->value);
			tmp = ft_malloc(len + 1, 1, 0);
			if (!tmp)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}
