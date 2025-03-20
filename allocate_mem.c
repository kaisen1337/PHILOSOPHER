/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:58:40 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/20 12:42:07 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_allocate(t_philo **philo, pthread_mutex_t **mutex, int number)
{
	*philo = malloc(number * sizeof(t_philo));
	if (!(*philo))
		return ((ft_printf(2, "Failed to allocate memory for philosophers\n"),
				-1));
	*mutex = malloc(number * sizeof(pthread_mutex_t));
	if (!(*mutex))
	{
		if (*philo)
		{
			free(*philo);
			*philo = NULL;
		}
		return ((ft_printf(2, "Failed to allocate memory for forks\n"), -1));
	}
	return (0);
}

void	ft_free(t_philo **philo, pthread_mutex_t **mutex)
{
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
	if (*mutex)
	{
		free(*mutex);
		*mutex = NULL;
	}
}
