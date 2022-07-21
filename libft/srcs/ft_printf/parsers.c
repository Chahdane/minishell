/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 22:08:57 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 01:55:49 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	reset_flags(t_flag	*flags)
{
	flags->f_width = 0;
	flags->minus = 0;
	flags->zero = 0;
	flags->prec = -1;
	flags->hash = 0;
	flags->spc = 0;
	flags->plus = 0;
	flags->size = 0;
}

static int	ft_isflag(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+');
}

static void	apply_flags(t_flag	*flags, char c)
{
	if (c == '-')
		flags->minus = 1;
	else if (c == '0')
		flags->zero = 1;
	else if (c == '#')
		flags->hash = 1;
	else if (c == ' ')
		flags->spc = 1;
	else if (c == '+')
		flags->plus = 1;
}

static int	ft_atoi(const char **str)
{
	int	nb;

	nb = 0;
	while (**str >= '0' && **str <= '9')
		nb = (nb * 10) + (*(*str)++ - '0');
	return (nb);
}

void	parse_flags(t_flag	*flags, const char **str)
{
	reset_flags(flags);
	while (ft_isflag(**str) && **str)
	{
		apply_flags(flags, **str);
		(*str)++;
	}
	flags->f_width = ft_atoi(str);
	if (**str == '.')
	{
		(*str)++;
		flags->zero = 0;
		flags->prec = ft_atoi(str);
	}
	if (**str == 'p')
		flags->hash = 1;
}
