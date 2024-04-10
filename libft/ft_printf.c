/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:52:22 by mbogey            #+#    #+#             */
/*   Updated: 2023/12/04 22:11:11 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_close_args(va_list args)
{
	va_end(args);
	return (-1);
}

static int	ft_other(va_list args, const char *format, size_t *count)
{
	if (*format == 'c')
		return (ft_putchar(va_arg(args, int), count));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *), count));
	else if (*format == 'p')
		return (ft_print_p(va_arg(args, unsigned long), count));
	else if (*format == 'd')
		return (ft_putnbr(va_arg(args, int), count));
	else if (*format == 'i')
		return (ft_putnbr(va_arg(args, int), count));
	else if (*format == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), DEC, count));
	else if (*format == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), HEXLOW, count));
	else if (*format == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), HEXUP, count));
	else
		return (ft_putchar(*format, count));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_other(args, format, &count) == -1)
				return (ft_close_args(args));
		}
		else
		{
			if (ft_putchar(*format, &count) == -1)
				return (ft_close_args(args));
		}
		format++;
	}
	va_end(args);
	return (count);
}
