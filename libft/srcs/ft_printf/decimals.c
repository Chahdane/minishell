/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 22:10:37 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 13:13:52 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

// d in funcation names stands for decimal
static char	*ft_fill_arr_d(unsigned int num, char *arr, char neg, t_flag flags)
{
	int	i;

	if (!arr)
		return (NULL);
	i = flags.size;
	arr[i--] = 0;
	i = left_adjust(arr, i, &flags);
	if (!num && flags.prec)
		arr[i--] = '0';
	while (num)
	{
		arr[i--] = '0' + num % 10;
		num /= 10;
	}
	i = print_zero(arr, i, &flags);
	if (flags.plus && !neg)
		arr[i--] = '+';
	else if (flags.spc && !neg)
		arr[i--] = ' ';
	else if (neg)
		arr[i--] = '-';
	right_adjust(arr, i, &flags);
	return (arr);
}

static char	*ft_allocate_num_d(unsigned int nbr, t_flag flags, char neg)
{
	int				size;
	char			*arr;
	unsigned int	num;

	size = 0;
	num = nbr;
	if (!nbr && flags.prec)
		size++;
	while (nbr)
	{
		size++;
		nbr /= 10;
	}
	flags.prec = handle_prec(num, flags, size);
	if (flags.prec > 0)
		size += flags.prec;
	if (neg || (!neg && (flags.spc || flags.plus)))
		size++;
	flags.f_width -= size;
	if (flags.f_width > 0)
		size += flags.f_width;
	arr = malloc(sizeof(char) * (size + 1));
	flags.size = size;
	return (ft_fill_arr_d(num, arr, neg, flags));
}

// converts unsigned ints
int	ft_putnbr_u(unsigned int nbr, t_flag flags)
{
	char	*arr;
	int		i;

	arr = ft_allocate_num_d(nbr, flags, 0);
	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		write(1, arr + i++, 1);
	free(arr);
	return (i);
}

// converts signed ints
int	ft_putnbr_s(int nbr, t_flag flags)
{
	char	*arr;
	int		i;

	if (nbr < 0)
		arr = ft_allocate_num_d((unsigned int)(-1 * nbr), flags, 1);
	else
		arr = ft_allocate_num_d((unsigned int)nbr, flags, 0);
	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		write(1, arr + i++, 1);
	free(arr);
	return (i);
}
