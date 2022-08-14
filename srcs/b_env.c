/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:07:40 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/14 16:52:10 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	list_len(void)
{
	int		count;
	t_env	*ptr;

	count = 0;
	ptr = g_data.env_lst;
	while (ptr)
	{
		if (ptr->value)
			count++;
		ptr = ptr->next;
	}
	return (count + 1);
}

void	fill_env(void)
{
	t_env	*ptr;
	char	*temp;
	char	**env;
	int		i;

	i = 0;
	ptr = g_data.env_lst;
	if (g_data.env)
		free_2d_array(g_data.env);
	env = malloc(sizeof(char *) * list_len());
	while (ptr)
	{
		if (ptr->value)
		{	
			temp = ft_strjoin(ptr->var, "=");
			env[i] = ft_strjoin(temp, ptr->value);
			free(temp);
			i++;
		}
		ptr = ptr->next;
	}
	env[i] = 0;
	g_data.env = env;
}

void	print_2d(void)
{
	int		i;
	char	**s2d;

	i = 0;
	fill_env();
	s2d = g_data.env;
	while (s2d[i])
	{
		printf("%s\n\n", s2d[i]);
		i++;
	}
}

void	env(void)
{
	t_env	*ptr;

	ptr = g_data.env_lst;

	g_data.exit_code = 0;
	while (ptr)
	{
		if (ptr->value[0] != 0)
			printf("%s=%s\n", ptr->var, ptr->value);
		ptr = ptr->next;
	}
}
