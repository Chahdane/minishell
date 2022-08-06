/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 23:46:01 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/07 00:01:33 by owahdani         ###   ########.fr       */
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
