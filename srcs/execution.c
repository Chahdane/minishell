/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:30:51 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/15 00:41:05 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_execute(void)
{
	t_cmd	*cmds;

	cmds = g_data.cmds;
	if (is_builtin(cmds) && !cmds->next)
		run_one_builtin();
	/* if fork and builtin, exit(g_data.exit_code)*/
}
