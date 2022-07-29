/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:19:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/29 20:07:07 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *name, char *error, int freeable)
{
	printf("%s: ", name);
	if (!error)
	{
		perror(NULL);
		return (-1);
	}
	printf("%s\n", error);
	if (freeable)
		free(error);
	return (-1);
}

void	join_error_str(char *error1, char *token)
{
	char	*str;
	char	*ptr;

	ptr = ft_strjoin(error1, token);
	if (check_malloc(ptr, NULL))
		return ;
	str = ft_strjoin(ptr, "\'");
	if (check_malloc(str, NULL))
		return ;
	free(ptr);
	g_data.exit_code = 258;
	ft_perror("minishell", str, 1);
}

int	check_malloc(void *to_be_checked, void *to_be_freed)
{
	if (to_be_checked)
		return (0);
	free(to_be_freed);
	ft_perror("minishell", NULL, 0);
	g_data.exit_code = 1;
	return (-1);
}
