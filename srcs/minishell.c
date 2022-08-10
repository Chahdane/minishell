/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/10 19:26:48 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void) ac;
	(void) av;
	init_env_lst(envp);

	//return 0;
	line = readline(PROMPT);
	while (line)
	{
		ft_add_history(line);
		/* if !parse_line, execute*/
		parse_line(line);
		//export(g_data.env_lst, g_data.cmds->args);
		//env(g_data.env_lst);
		print_in();
		free(line);
		clear_cmds_lst(g_data.cmds);
		line = readline(PROMPT);
	}
	
	return (0);
}
