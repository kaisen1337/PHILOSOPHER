/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:50:29 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/19 16:28:45 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr(int fd, char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar(fd, *str, counter);
		str++;
	}
}

static void	ft_putnbr(int fd, int nb, int *counter)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar(fd, '-', counter);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(fd, n / 10, counter);
	}
	ft_putchar(fd, n % 10 + '0', counter);
}

static void	ft_putnbr_long(int fd, long nb, int *counter)
{
	if (nb < 0)
	{
		ft_putchar(fd, '-', counter);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_long(fd, nb / 10, counter);
	}
	ft_putchar(fd, nb % 10 + '0', counter);
}

static void	format_specifier(int fd, va_list arguements, char specifier,
		int *counter)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr(fd, va_arg(arguements, int), counter);
	else if (specifier == 's')
		ft_putstr(fd, (char *)va_arg(arguements, char *), counter);
	if (specifier == 'l')
		ft_putnbr_long(fd, va_arg(arguements, long), counter);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	arguements;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	va_start(arguements, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			format_specifier(fd, arguements, str[i], &counter);
			if (str[i] == 'l' && str[i + 1] == 'd')
				i++;
		}
		else
			ft_putchar(fd, str[i], &counter);
		i++;
	}
	va_end(arguements);
	return (counter);
}
