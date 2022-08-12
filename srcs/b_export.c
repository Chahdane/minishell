/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:49 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/12 15:26:08 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_arg(char *arg)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * 4);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
	{
		tab[0] = ft_substr(arg, 0, i - 1);
		tab[2] = ft_strdup("+");
	}
	else
	{
		tab[0] = ft_substr(arg, 0, i);
		tab[2] = ft_strdup("-");
	}
	arg++;
	tab[1] = ft_substr(arg + i, 0, ft_strlen(arg) - i);
	tab[3] = 0;
	return (tab);
}

void	add_node(t_env **lst, char *var, char *value)
{
	t_env	*ptr;
	t_env	*new;

	if (!lst)
		return ;
	new = malloc(sizeof(t_env));
	new->var = var;
	new->value = value;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	replace_val(t_env *env, int index, char *new_value, int flag)
{
	int	i;

	i = -1;
	while (i++ < index && env->next)
		env = env->next;
	if (!flag)
		env->value = new_value;
	else
		env->value = ft_strjoin(env->value, new_value);
}

int	check_naming(char *str, char *str2)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("minishell: export: `%s", str);
		if (str2[0] != 0)
			printf("=%s", str2);
		printf("': not a valid identifier\n");
		return (-1);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: export: `%s", str);
			if (str2[0] != 0)
				printf("=%s", str2);
			printf("': not a valid identifier\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

void	export(t_env *env, char **args)
{
	int		i;
	char	**sp_arg;

	if (!args)
	{
		print_export();
		return ;
	}
	i = 0;
	while (args[i])
	{
		sp_arg = split_arg(args[i]);
		if (check_naming(sp_arg[0], sp_arg[1]) == 1)
		{
			if (sp_arg[2][0] == '-' && search_var(env, sp_arg[0]) > -1)
				replace_val(env, search_var(env, sp_arg[0]) - 1, sp_arg[1], 0);
			else if (search_var(env, sp_arg[0]) == -1)
				add_node(&env, sp_arg[0], sp_arg[1]);
			else if (sp_arg[2][0] == '+' && search_var(env, sp_arg[0]) > -1)
				replace_val(env, search_var(env, sp_arg[0]) - 1, sp_arg[1], 1);
		}
		i++;
	}
}
