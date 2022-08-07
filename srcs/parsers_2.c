/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:46:01 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/07 20:24:00 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_names_lst(t_name *name_lst)
{
	t_name	*tmp;

	while (name_lst)
	{
		tmp = name_lst->next;
		free(name_lst->name);
		free(name_lst);
		name_lst = tmp;
	}
}

int	add_name(t_name **name_lst, t_token *token)
{
	t_name	*new;

	if (!*name_lst)
	{
		new = ft_malloc(1, sizeof(t_name), 0);
		*name_lst = new;
	}
	else
	{
		new = *name_lst;
		while (new->next)
			new = new->next;
		new->next = ft_malloc(1, sizeof(t_name), 0);
		new = new->next;
	}
	if (!new)
		return (-1);
	new->next = NULL;
	new->name = ft_strdup(token->value);
	if (!new->name)
		return (-1);
	new->out_mode = NEW;
	if (token->type == APPF)
		new->out_mode = APP;
	return (0);
}

static int	name_lst_size(t_name *name_lst)
{
	int	i;

	i = 0;
	while (name_lst)
	{
		i++;
		name_lst = name_lst->next;
	}
	return (i);
}

int	args_lst_to_arr(t_cmd **cmd)
{
	int		i;
	t_name	*tmp;

	if (!(*cmd)->args_lst)
	{
		(*cmd) = (*cmd)->next;
		return (0);
	}
	i = name_lst_size((*cmd)->args_lst);
	(*cmd)->args = ft_malloc(i + 1, sizeof(char *), 0);
	if (!(*cmd)->args)
		return (-1);
	tmp = (*cmd)->args_lst;
	i = 0;
	while (tmp)
	{
		((*cmd)->args)[i++] = tmp->name;
		tmp = tmp->next;
	}
	((*cmd)->args)[i] = NULL;
	(*cmd) = (*cmd)->next;
	return (0);
}
