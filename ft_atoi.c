/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:03:31 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/08 10:21:10 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(int fd, char c, int *counter)
{
	write(fd, &c, 1);
	(*counter)++;
}

static int	is_overflow(long result, int digit)
{
	if (result > 214748364)
		return (1);
	if (result == 214748364 && digit > 7)
		return (1);
	return (0);
}

void	init_var(int *v1, long *v2, size_t *v3)
{
	*v1 = 1;
	*v2 = 0;
	*v3 = 0;
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	init_var(&sign, &result, &i);
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
	{
		if (is_overflow(result, str[i] - '0'))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		result = result * 10 + (str[i++] - '0');
	}
	return (sign * result);
}
