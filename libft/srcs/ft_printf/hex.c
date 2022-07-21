/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:18:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/01/13 13:16:38 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	print_hash(char *arr, int i, t_flag flags, char conv)
{
	if (conv == 'p' || flags.hash)
	{
		if (conv == 'p' || conv == 'x')
			arr[i--] = 'x';
		else
			arr[i--] = 'X';
		arr[i--] = '0';
	}
	return (i);
}

static char	extract_hex(unsigned char num, char conv)
{
	if (num < 10)
		return ('0' + num);
	if (conv == 'p' || conv == 'x')
		return ('a' + num - 10);
	return ('A' + num - 10);
}

// 'x' in function names stands for hexadecimal
static char	*ft_fill_arr_x(unsigned long num,
	char *arr, char conv, t_flag flags)
{
	int	i;

	if (!arr)
		return (NULL);
	i = flags.size;
	arr[i--] = 0;
	i = left_adjust(arr, i, &flags);
	if (!num && (flags.prec || conv == 'p'))
		arr[i--] = '0';
	if (!num)
		flags.hash = 0;
	while (num)
	{
		arr[i--] = extract_hex(num % 16, conv);
		num /= 16;
	}
	i = print_zero(arr, i, &flags);
	i = print_hash(arr, i, flags, conv);
	right_adjust(arr, i, &flags);
	return (arr);
}

static char	*ft_allocate_num_x(unsigned long nbr, t_flag flags, char conv)
{
	unsigned long	num;
	int				size;
	char			*arr;

	size = 0;
	num = nbr;
	if (!nbr && flags.prec)
		size++;
	while (nbr)
	{
		size++;
		nbr /= 16;
	}
	flags.prec = handle_prec(num, flags, size);
	if (flags.prec > 0)
		size += flags.prec;
	if (conv == 'p' || (num && flags.hash))
		size += 2;
	flags.f_width -= size;
	if (flags.f_width > 0)
		size += flags.f_width;
	flags.size = size;
	arr = malloc(sizeof(char) * (size + 1));
	return (ft_fill_arr_x(num, arr, conv, flags));
}

int	ft_hex(unsigned long nbr, t_flag flags, char conv)
{
	char	*arr;
	int		i;

	arr = ft_allocate_num_x(nbr, flags, conv);
	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		write(1, arr + i++, 1);
	free(arr);
	return (i);
}
