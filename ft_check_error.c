/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:38:21 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/08 10:10:07 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_arithmetic_operator(char c)
{
	return (c == '+' || c == '-');
}

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !is_arithmetic_operator(str[i]))
			return (0);
		if (is_arithmetic_operator(str[i]) && i != 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_error(int ac, char **av, int *number)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return ((ft_printf(2, "Eroor \nthe arguements must be 5 or 6 \n"), 0));
	while (av[i])
	{
		if (!is_all_digit(av[i]))
			return ((ft_printf(2, "Eroor \nthe arg %d is not a valid number \n",
						i), 0));
		if (ft_atoi(av[i]) <= 0)
			return ((ft_printf(2,
						"Eroor \nthe arg%d must not be negative or eq 0 \n", i),
					0));
		i++;
	}
	*number = ft_atoi(av[1]);
	if (*number > 200)
	{
		ft_printf(2,
			"Eroor\nthe number of the philosophers must be less than 200\n", i);
		return (0);
	}
	return (1);
}
