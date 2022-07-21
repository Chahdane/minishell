/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:46:17 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/31 21:38:09 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// unlike ft_atoi, this function handles over/underflows && non-numeric inputs
int	ft_strtoi(const char *str, int *errnum)
{
	long	nbr;
	int		s;
	int		i;

	*errnum = 1;
	i = 0;
	if (!str[i])
		return (-1);
	s = 1;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	nbr = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i++] - '0');
		if ((nbr > INT_MAX && s == 1) || (nbr > 2147483648 && s == -1))
			return (-1);
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-1);
	*errnum = 0;
	return ((int)(nbr * s));
}
