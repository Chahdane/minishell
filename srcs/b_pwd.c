/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:11:19 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/10 21:25:05 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	t_env	*env;

    env = g_data.env_lst;
    while (env)
    {
        if (ft_strcmp(env->var, "PWD") == 0)
            printf("%s\n", env->value);
        env = env->next;
    }
    g_data.exit_code = 0;
}