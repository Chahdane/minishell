/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 02:22:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 13:20:34 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// struct data type to hold flag and size information about conversions
typedef struct s_flag
{
	int		f_width;
	char	minus;
	char	zero;
	int		prec;
	char	hash;
	char	spc;
	char	plus;
	int		size;
}				t_flag;

int		ft_printf(const char *str, ...);
void	parse_flags(t_flag	*flags, const char **str);
int		ft_putchar_c(unsigned char c, t_flag flags);
int		ft_putnbr_s(int nbr, t_flag flags);
int		left_adjust(char *arr, int i, t_flag *flags);
int		print_zero(char *arr, int i, t_flag *flags);
int		print_percent(t_flag flags);
int		handle_prec(unsigned long num, t_flag flags, int size);
int		ft_putnbr_u(unsigned int nbr, t_flag flags);
int		ft_hex(unsigned long nbr, t_flag flags, char conv);
void	right_adjust(char *arr, int i, t_flag *flags);
int		ft_putstr_s(char *str, t_flag flags);

#endif
