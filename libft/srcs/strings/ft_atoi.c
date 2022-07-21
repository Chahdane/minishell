/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:10:57 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/17 15:44:03 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	nb;

	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	nb = 0;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*str++ - '0');
	return (nb * sign);
}
