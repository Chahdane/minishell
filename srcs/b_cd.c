/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:51:05 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/15 19:09:41 by achahdan         ###   ########.fr       */
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
			break ;
		}
		env = env->next;
	}
	free(pwd);
}

void	go_home(void)
{
	t_env	*env;

	env = g_data.env_lst;
	if (sv(g_data.env_lst, "HOME") == -1)
	{
		printf("minishell: cd: HOME not set\n");
		g_data.exit_code = 1;
		return ;
	}
	else
	{
		while (env)
		{
			if (ft_strncmp("HOME", env->var, 5) == 0)
			{
				if (chdir(env->value) != 0)
				{
					printf("minishell: cd: %s: No such file or directory\n", env->value);
					g_data.exit_code = 1;
				}
				break ;
			}
			env = env->next;
		}
	}
}

void	cd(t_cmd *cmd)
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
		replace_val(g_data.env_lst, sv(g_data.env_lst, "OLDPWD") - 1, cwd, 0);
	free(cwd);
	g_data.exit_code = 0;
	args = cmd->args + 1;
	if (!*args)
		go_home();
	else if (chdir(args[0]) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		g_data.exit_code = 1;
	}
	update_env_pwd("PWD", 3);
}
