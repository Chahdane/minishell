/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:07:40 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/08 21:30:24 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    env(t_env *env)
{
    t_env   *ptr;

    ptr = env;
    while (ptr)
    {
        if (ptr->value)
            printf("%s=%s\n", ptr->var, ptr->value);
        ptr = ptr->next;
    }
}