/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:50:29 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/11 15:10:49 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_putstr(char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar(*str, counter);
		str++;
	}
}

void	ft_putnbr(int nb, int *counter)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-', counter);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, counter);
	}
	ft_putchar(n % 10 + '0', counter);
}
void ft_putnbr_long(long nb, int *counter)
{
    if (nb < 0)
    {
        ft_putchar('-', counter);
        nb = -nb;
    }
    if (nb >= 10)
    {
        ft_putnbr_long(nb / 10, counter);
    }
    ft_putchar(nb % 10 + '0', counter);
}

void	format_specifier(va_list arguements, char specifier, int *counter)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(arguements, int), counter);
	else if (specifier == 's')
		ft_putstr((char *)va_arg(arguements, char *), counter);
	if (specifier == 'l')
		ft_putnbr_long(va_arg(arguements, long), counter);	
}

int	ft_printf(const char *str, ...)
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
			format_specifier(arguements, str[i], &counter);
			if(str[i] == 'l' && str[i + 1] == 'd')
				i++;
		}
		else
			ft_putchar(str[i], &counter);
		i++;
	}
	va_end(arguements);
	return (counter);
}
