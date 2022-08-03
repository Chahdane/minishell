/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:43:13 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/04 00:01:57 by owahdani         ###   ########.fr       */
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

int	len_after_expand(char *value)
{
	len = ft_strlen(token->value);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			mv_2_nxt_quote(token->value, &i)
		else if (token->value[i] == '\"')
		{
			i++;
			while (token->value[i] != '\"')
			{
				if (token->value[i] == '$')
				{
					if (token->value[++i] == '?')
						len++;
					else if (is_alpha(token->value[i]))
						len += value_len(token->value, &i);
					else
						i++;
				}
				else
					i++;
			}
		}
		else if (token->value[i] == '$')
		{
			if (token->value[++i] == '?')
				len++;
			else if (is_alpha(token->value[i]))
				len += value_len(token->value, &i);
			else
				i++;
		}
		else
			i++;
	}
}

int	ft_expand(t_token *token)
{
	int	len;
	int		i;

	while (token)
	{
		if (token->type != HRDOC && token->type != PIPE)
		{
			len = ft_strlen(token->value);
			i = 0;
			while (token->value[i])
			{
				if (token->value[i] == '\'')
					mv_2_nxt_quote(token->value, &i)
				else if (token->value[i] == '\"')
				{
					i++;
					while (token->value[i] != '\"')
					{
						if (token->value[i] == '$')
						{
							if (token->value[++i] == '?')
								len++;
							else if (is_alpha(token->value[i]))
								len += value_len(token->value, &i);
							else
								i++;
						}
						else
							i++;
					}
				}
				else if (token->value[i] == '$')
				{
					if (token->value[++i] == '?')
						len++;
					else if (is_alpha(token->value[i]))
						len += value_len(token->value, &i);
					else
						i++;
				}
				else
					i++;
			}
		}
		token = token->next;
	}
	return (0);
}
