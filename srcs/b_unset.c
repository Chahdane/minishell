/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:13:07 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/12 23:50:48 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	del_head(t_env **head, t_env *temp)
{
	*head = (*head)->next;
	free(temp);
}

int	check_unset_naming(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		g_data.exit_code = 1;
		return (-1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", str);
			g_data.exit_code = 1;
			return (-1);
		}
		i++;
	}
	return (1);
}

void	delete_node(t_env **head, int pos, t_env *temp, t_env *prev)
{
	int	i;

	i = -1;
	while (i++ < pos)
	{
		if (i == 0 && pos == 1)
			del_head(head, temp);
		else
		{
			if (i == pos - 1 && temp)
			{
				prev->next = temp->next;
				free(temp);
			}
			else
			{
				prev = temp;
				if (prev == NULL)
					break ;
				temp = temp->next;
			}
		}
	}
}

void	search_and_unset(char *str)
{
	t_env	*env;
	t_env	*temp;
	t_env	*prev;
	int		pos;

	pos = 1;
	env = g_data.env_lst;
	temp = env;
	prev = env;
	while (env)
	{
		if (ft_strcmp(env->var, str) == 0)
			delete_node(&g_data.env_lst, pos, temp, prev);
		env = env->next;
		pos++;
	}
}

void	unset(void)
{
	t_env	*env;
	char	**args;
	int		i;

	i = 0;
	env = g_data.env_lst;
	args = g_data.cmds->args;
	while (args[i])
	{
		if (check_unset_naming(args[i]) == 1)
			search_and_unset(args[i]);
		i++;
	}
	//fill_env();
}
