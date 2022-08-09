/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:23:07 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/09 16:58:30 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_value_from_env(char *value, int *i)
{
	int		j;
	char	*tmp;
	t_env	*tmp_env;

	j = 0;
	while (ft_isalnum(value[*i + j]) || value[*i + j] == '_')
		j++;
	tmp = ft_strndup(value + *i, j);
	(*i) += j;
	tmp_env = g_data.env_lst;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->var, tmp))
			break ;
		tmp_env = tmp_env->next;
	}
	free(tmp);
	if (!tmp_env)
		return (NULL);
	return (tmp_env->value);
}

void	check_n_expand(char *value, char *new, int *i, int *j)
{
	int		k;
	char	*tmp;

	k = 0;
	if (value[*i] == '$' && value[*i + 1] == '?')
	{
		(*i) += 2;
		tmp = ft_itoa(g_data.exit_code);
		while (tmp[k])
			new[(*j)++] = tmp[k++];
		free(tmp);
	}
	else if (value[*i] == '$' && ft_isalpha(value[*i + 1]))
	{
		(*i)++;
		tmp = get_value_from_env(value, i);
		while (tmp && tmp[k])
			new[(*j)++] = tmp[k++];
	}
	else
		new[(*j)++] = value[(*i)++];
}

void	remove_quotes(char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			while (value[++i] != '\'')
				value[j++] = value[i];
		else if (value[i] == '\"')
			while (value[++i] != '\"')
				value[j++] = value[i];
		else
			value[j++] = value[i];
		i++;
	}
	value[j] = 0;
}
