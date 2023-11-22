/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elakhfif <elakhfif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 03:26:54 by elakhfif          #+#    #+#             */
/*   Updated: 2023/11/22 03:26:56 by elakhfif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void	ohmyputstr(char *str, int *lenth)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
		(*lenth)++;
	}
}

void	ohmyputdigit(long long int num, int base, int *lenth)
{
	char	*hexa = "0123456789abcdef";
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
		(*lenth)++;
	}
	if (num >= base)
		ohmyputdigit(num / base, base, lenth);
	write(1, &hexa[num % base], 1);
	(*lenth)++;
}

int	ft_printf(const char *format, ...)
{
	int	lenth = 0;
	va_list	ptr;
	va_start(ptr, format);
	while(*format)
	{
		if (*format == '%' && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				ohmyputstr(va_arg(ptr, char *), &lenth);
			else if (*format == 'd')
				ohmyputdigit((long long int)va_arg(ptr, int), 10, &lenth);
			else if (*format == 'x')
				ohmyputdigit((long long int)va_arg(ptr, unsigned int), 16, &lenth);
		}
		else
			lenth += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), lenth);
}

int	main()
{
	int	a = 42;
	char	*str = "Hello World!";
	ft_printf("Hello %s! %d %x\n", str, a, a);
	return (0);
}
