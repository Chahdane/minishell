/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:44:07 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/10 20:00:16 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

t_env	*clone_list(void)
{
	t_env	*newlist;
	t_env	*p;
	t_env	*prev;
	t_env	*list;

	list = g_data.env_lst;
	newlist = NULL;
	p = NULL;
	while (list)
	{
		p = malloc(sizeof(*p));
		p->var = list->var;
		p->value = list->value;
		if (!newlist)
			newlist = p;
		else
			prev->next = p;
		prev = p;
		list = list->next;
	}
	prev->next = NULL;
	return (newlist);
}

void	find_smallest(t_env *env)
{
	t_env	*small;	
	t_env	*prev;

	small = env;
	while (env->next)
	{
		if (ft_strcmp(env->var, env->next->var) > 0)
		{
			prev = env;
			small = env->next;
		}
		env = env->next;
	}
	printf("%s\n", small->var);
	if (small->next)
	{
		if (prev)
			prev->next = small->next;
		else
			env = small->next;
	}
	else
		prev->next = NULL;
	free(small);
}

void	print_in(void)
{
	t_env	*new;
	int		i;

	i = 0;
	new = clone_list();
	while (i < 2)
	{
		find_smallest(new);
		i++;
	}
	printf("\n\nnew\n\n");
	while (new)
	{
		printf("%s\n", new->var);
		new = new->next;
	}
}

int	search_var(t_env *env, const char *var)
{
	int	i;

	i = 0;
	while (env)
	{
		if (strncmp(env->var, var, strlen(var)) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (-1);
}
