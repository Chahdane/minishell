/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:19:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/11 21:04:17 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *name, char *error, int freeable)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (!error)
	{
		perror(NULL);
		return (-1);
	}
	ft_putendl_fd(error, 2);
	if (freeable)
		free(error);
	return (-1);
}

void	join_error_str(char *error1, char *token)
{
	char	*str;
	char	*ptr;

	ptr = ft_strjoin(error1, token);
	if (check_malloc(ptr, NULL, 0))
		return ;
	str = ft_strjoin(ptr, "\'");
	if (check_malloc(str, NULL, 0))
		return ;
	free(ptr);
	g_data.exit_code = 258;
	ft_perror("minishell", str, 1);
}

int	check_malloc(void *to_be_checked, void *to_be_freed, int is_exit)
{
	if (to_be_checked)
		return (0);
	free(to_be_freed);
	ft_perror("minishell", NULL, 0);
	g_data.exit_code = 1;
	if (is_exit)
		exit (1);
	return (-1);
}
