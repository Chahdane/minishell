/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:19:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/21 14:33:24 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *name, char *error)
{
	printf("%s: ", name);
	if (!error)
	{
		perror(NULL);
		return (-1);
	}
	printf("%s\n", error);
	return (-1);
}
