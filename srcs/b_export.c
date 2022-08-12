/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:49 by achahdan          #+#    #+#             */
/*   Updated: 2022/08/13 00:23:01 by achahdan         ###   ########.fr       */
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
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
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
	char	*temp;
	i = -1;
	temp = NULL;
	while (i++ < index && env->next)
		env = env->next;
	if (!flag)
	{
		temp = ft_strdup(new_value);
		free(env->value);
		env->value = temp;
	}
	else
	{
		temp = ft_strjoin(env->value, new_value);
		free(env->value);
		env->value = temp;
	}
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
		g_data.exit_code = 1;
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
			g_data.exit_code = 1;
			return (-1);
		}
		i++;
	}
	return (1);
}

void	export(t_env *env, char **args)
{
	int		i;
	char	**sp;

	if (!args)
	{
		print_export();
		return ;
	}
	i = 0;
	while (args[i])
	{
		sp = split_arg(args[i]);
		if (check_naming(sp[0], sp[1]) == 1)
		{
			if (sp[2][0] == '-' && sv(env, sp[0]) > -1 && sp[1][0] != 0)
				replace_val(env, sv(env, sp[0]) - 1, sp[1], 0);
			else if (sv(env, sp[0]) == -1)
				add_node(&env, sp[0], sp[1]);
			else if (sp[2][0] == '+' && sv(env, sp[0]) > -1 && sp[1][0] != 0)
				replace_val(env, sv(env, sp[0]) - 1, sp[1], 1);
		}
		free_2d_array(sp);
		i++;
	}
	fill_env();
}


/// export without value does no overwrite
// echo with -p