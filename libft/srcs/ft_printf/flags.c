/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:22:17 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 17:04:27 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	left_adjust(char *arr, int i, t_flag *flags)
{
	if (flags->minus)
		while (flags->f_width-- > 0)
			arr[i--] = ' ';
	return (i);
}

int	print_zero(char *arr, int i, t_flag *flags)
{
	if (flags->prec > 0)
		while (flags->prec-- > 0)
			arr[i--] = '0';
	else if (flags->zero)
		while (flags->f_width-- > 0)
			arr[i--] = '0';
	return (i);
}

void	right_adjust(char *arr, int i, t_flag *flags)
{
	while (flags->f_width-- > 0 && i > -1)
		arr[i--] = ' ';
}

int	print_percent(t_flag flags)
{
	int	count;

	count = 0;
	flags.f_width--;
	if (!flags.minus)
		while (flags.f_width-- > 0)
			count += write(1, " ", 1);
	count += write(1, "%", 1);
	if (flags.minus)
		while (flags.f_width-- > 0)
			count += write(1, " ", 1);
	return (count);
}

int	handle_prec(unsigned long num, t_flag flags, int size)
{
	if (num)
		return (flags.prec - size);
	if (flags.prec != 1 && flags.prec > -1)
		return (flags.prec - size);
	return (-1);
}
