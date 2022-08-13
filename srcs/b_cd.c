/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:51:05 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/13 03:13:36 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_env_pwd(void)
{
	t_env	*env;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	g_data.exit_code = 0;
	env = g_data.env_lst;
	while (env)
	{
		if (ft_strncmp(env->var, "PWD", 3) == 0)
		{
			free(env->value);
			env->value = ft_strdup(pwd);
			free(pwd);
			break;
		}
		env = env->next;
	}
}

void    cd(char **envp)
{
    char	**args;
	char	*home_dir;
	int		i;

	home_dir = NULL;
	i = 0;
	while (envp[i])
	{
		if(ft_strncmp("HOME=",envp[i],5) == 0)
		{
			home_dir = envp[i] + 5;
			break;
		}
		i++;
	}
	args = g_data.cmds->args;
    if (args == NULL)
        chdir(home_dir);
	else if (chdir(args[0]) != 0)
        printf("minishell: cd: %s: No such file or directory", args[0]);
    update_env_pwd();
}