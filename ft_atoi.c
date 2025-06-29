/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:03:31 by nkasimi           #+#    #+#             */
/*   Updated: 2025/06/29 08:40:05 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(int fd, char c, int *counter)
{
	write(fd, &c, 1);
	(*counter)++;
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		result = result * 10 + (str[i++] - '0');
	return (sign * result);
}
