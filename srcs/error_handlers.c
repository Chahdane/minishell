/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:19:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 19:04:25 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *name, char *error, int free)
{
	printf("%s: ", name);
	if (!error)
	{
		perror(NULL);
		return (-1);
	}
	printf("%s\n", error);
	if (free)
		free(error);
	return (-1);
}

void join_error_str(char *error1, char *token)
{
	char	*str;
	char	*ptr;

	ptr = ft_strjoin(error1, token);
	if (check_malloc(str, NULL))
		return ;
	str = ft_strjoin(ptr, "\'");
	if (check_malloc(str, NULL))
		return ;
	free(ptr);
	g_data.exit_code = 258;
	ft_perror("minishell", str, 1);
}
