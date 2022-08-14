/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:51:05 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/14 01:16:46 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_env_pwd(char *var, int len)
{
	t_env	*env;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	g_data.exit_code = 0;
	env = g_data.env_lst;
	while (env)
	{
		if (ft_strncmp(env->var, var, len) == 0)
		{
			free(env->value);
			env->value = ft_strdup(pwd);
			free(pwd);
			break ;
		}
		env = env->next;
	}
}

void	cd()
{
	char	**args;
	int		i;
	char	*cwd;

	i = 0;

	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);

	if (sv(g_data.env_lst, "OLDPWD") == -1)
		add_node(&g_data.env_lst, "OLDPWD", cwd);
	else
		replace_val(g_data.env_lst, sv(g_data.env_lst, "OLDPWD") -1, cwd, 0);
	free(cwd);
	// print error + go home
	args = g_data.cmds->args + 1;
	if (chdir(args[0]) != 0)
        printf("minishell: cd: %s: No such file or directory", args[0]);
    update_env_pwd("PWD", 3);
}

//add pipe flag;