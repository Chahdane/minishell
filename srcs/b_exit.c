/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:34:24 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/14 18:30:26 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_isdigit(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		flag = 1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (flag == 1 && i == 1)
		return (0);
	return (1);
}

int	check_args(char **args)
{
	if (!str_isdigit(args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		exit(255);
	}
	if (args[1])
	{
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	char	**args;

	args = cmd->args + 1;
	if (!*args)
		exit(0);
	if (check_args(args))
		exit(ft_atoi(args[0]) % 256);
}
