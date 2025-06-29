/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisen1337 <kaisen1337@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:58:40 by nkasimi           #+#    #+#             */
/*   Updated: 2025/06/28 05:26:41 by kaisen1337       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_allocate(t_philo **philo, pthread_mutex_t **lock, int number)
{
	*philo = malloc(number * sizeof(t_philo));
	if (!(*philo))
		return ((ft_printf(2, "Failed to allocate memory for philosophers\n"),
				0));
	*lock = malloc(number * sizeof(pthread_mutex_t));
	if (!(*lock))
	{
		if (*philo)
		{
			free(*philo);
			*philo = NULL;
		}
		return ((ft_printf(2, "Failed to allocate memory for forks\n"), 0));
	}
	return (1);
}

void	ft_free(t_philo **philo, pthread_mutex_t **lock)
{
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
	if (*lock)
	{
		free(*lock);
		*lock = NULL;
	}
}
