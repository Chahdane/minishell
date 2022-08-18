/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:11:19 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/18 17:34:30 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	g_data.exit_code = 0;
	if (!pwd)
	{
		printf("minishell: directory does not exist\n");
		g_data.exit_code = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}
