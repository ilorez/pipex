/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:01:35 by znajdaou          #+#    #+#             */
/*   Updated: 2024/12/31 13:10:12 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_hexa(unsigned long n, char *base)
{
	int	out_len;

	out_len = 0;
	if (n >= 16)
		out_len += ft_print_hexa(n / 16, base);
	out_len += ft_print_char(base[n % 16]);
	return (out_len);
}

int	ft_print_nbr(int nbr)
{
	long	n;
	int		out_len;

	n = nbr;
	out_len = 0;
	if (n < 0)
	{
		out_len += ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
		out_len += ft_print_nbr(n / 10);
	out_len += ft_print_char(n % 10 + 48);
	return (out_len);
}

int	ft_print_ptr(void *ptr)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_print_hexa((unsigned long)ptr,
			"0123456789abcdef"));
}

int	ft_print_str(char *str)
{
	int	out_len;

	out_len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
	{
		out_len += ft_print_char(*str);
		str++;
	}
	return (out_len);
}
