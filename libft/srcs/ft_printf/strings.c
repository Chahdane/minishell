/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:11:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 02:11:48 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putchar_c(unsigned char c, t_flag flags)
{
	int	i;

	i = 1;
	if (!flags.minus)
	{
		while (i < flags.f_width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	write(1, &c, 1);
	if (flags.minus)
	{
		while (i < flags.f_width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	return (i);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr_s(char *str, t_flag flags)
{
	int	i;
	int	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.prec == -1)
		flags.prec = len;
	if (len > flags.prec)
		flags.f_width -= flags.prec;
	else
		flags.f_width -= len;
	len = 0;
	if (!flags.minus)
		while (flags.f_width-- > 0)
			len += ft_putchar(' ');
	i = 0;
	while (str[i] && i < flags.prec)
		ft_putchar(str[i++]);
	len += i;
	if (flags.minus)
		while (flags.f_width-- > 0)
			len += ft_putchar(' ');
	return (len);
}
