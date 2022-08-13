/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:51:05 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/13 23:58:16 by achahdan         ###   ########.fr       */
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

void	cd(char **envp)
{
	char	**args;
	char	*home_dir;
	int		i;

	home_dir = NULL;
	i = 0;
	update_env_pwd("OLDPWD", 6);
	while (envp[i])
	{
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
		{
			home_dir = envp[i] + 5;
			break ;
		}
		i++;
	}
	// print error
	args = g_data.cmds->args + 1;
    if (*args == NULL)
        chdir(home_dir);
	else if (chdir(args[0]) != 0)
        printf("minishell: cd: %s: No such file or directory", args[0]);
    update_env_pwd("PWD", 3);
}
