/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:38:21 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/01 11:01:40 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] == '+'))
		{
			return (0);
		}
		if ((str[i] == '+') && (str[i - 1] >= '0' && str[i - 1] <= '9')
			&& i > 0)
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
		if (ft_isdigit(av[i]) == 0)
			return ((ft_printf(2, "Eroor \nthe arg %d is not a valid number \n",
						i), 0));
		if (ft_atoi(av[i]) <= 0)
			return ((ft_printf(2, "Eroor \nthe arg %d must not be 0 \n", i),
					0));
		i++;
	}
	*number = ft_atoi(av[1]);
	if (*number > 200)
		return ((ft_printf(2,
					"Eroor\nthe number of the philosophers must be less than 200\n",
					i), 0));
	return (1);
}
