/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 02:20:49 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 17:04:53 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	apply_formats(const char **str, t_flag *flags, va_list ap)
{
	int	count;

	parse_flags(flags, str);
	count = 0;
	if (**str == '%')
		count = print_percent(*flags);
	else if (**str == 'c')
		count = ft_putchar_c((unsigned char)va_arg(ap, int), *flags);
	else if (**str == 'i' || **str == 'd')
		count = ft_putnbr_s(va_arg(ap, int), *flags);
	else if (**str == 'u')
		count = ft_putnbr_u(va_arg(ap, unsigned int), *flags);
	else if (**str == 'x' || **str == 'X')
		count = ft_hex(va_arg(ap, unsigned int), *flags, **str);
	else if (**str == 'p')
		count = ft_hex((unsigned long)va_arg(ap, void *), *flags, **str);
	else if (**str == 's')
		count = ft_putstr_s(va_arg(ap, char *), *flags);
	(*str)++;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int			count;
	t_flag		flags;
	va_list		ap;

	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += apply_formats(&str, &flags, ap);
		}
		else
			count += write(1, str++, 1);
	}
	va_end(ap);
	return (count);
}
