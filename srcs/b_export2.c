/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:44:07 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/17 01:50:20 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*clone_list(void)
{
	t_env	*new;
	t_env	*ptr;
	t_env	*prev;
	t_env	*list;

	list = g_data.env_lst;
	new = NULL;
	ptr = NULL;
	while (list)
	{
		ptr = malloc(sizeof(t_env));
		ptr->var = list->var;
		ptr->value = list->value;
		if (!new)
			new = ptr;
		else
			prev->next = ptr;
		prev = ptr;
		list = list->next;
	}
	prev->next = NULL;
	return (new);
}

t_env	*sorted_list(t_env *env)
{
	t_env	*ptr;
	char	*temp;

	ptr = env;
	while (ptr->next)
	{
		if (ft_strcmp(ptr->var, ptr->next->var) > 0)
		{
			temp = ptr->var;
			ptr->var = ptr->next->var;
			ptr->next->var = temp;
			temp = ptr->value;
			ptr->value = ptr->next->value;
			ptr->next->value = temp;
			ptr = env;
		}
		else
			ptr = ptr->next;
	}
	return (env);
}

void	print_export(void)
{
	t_env	*new;
	t_env	*ptr;
	t_env	*temp;

	new = clone_list();
	new = sorted_list(new);
	ptr = new;
	while (new)
	{
		if (new->value[0] == 0)
			printf("declare -x %s\n", new->var);
		else
			printf("declare -x %s=\"%s\"\n", new->var, new->value);
		new = new->next;
	}
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
}

int	co(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (1);
}

// search for var
int	sv(t_env *env, char *var)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (-1);
}
