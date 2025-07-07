/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:44:20 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/02 08:23:23 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat_n = ft_atoi(av[5]);
	else
		data->must_eat_n = -1;
	data->stop = 0;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->check_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->check_lock);
		return (0);
	}
	return (1);
}

int	ft_init_philo(t_philo *philo, t_data *data, pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i;
		philo[i].meals_counter = 0;
		philo[i].time_of_last_meal = get_current_time();
		philo[i].data = data;
		philo[i].left_f = &lock[i];
		philo[i].right_f = &lock[(i + 1) % data->num_of_philo];
		if (pthread_create(&philo[i].thrd_id, NULL, day_of_philo,
				&philo[i]) != 0)
		{
			data->stop = 1;
			while (i > 0)
			{
				i--;
				pthread_join(philo[i].thrd_id, NULL);
			}
			return ((ft_printf(2, "pthread_creat failed\n"), 0));
		}
		i++;
	}
	return (1);
}

int	ft_init_mutex(t_data *data, pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&lock[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&lock[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_init(t_data *data, pthread_mutex_t *lock, char **av)
{
	if (!ft_init_data(data, av))
		return (0);
	if (!ft_init_mutex(data, lock))
		return (0);
	return (1);
}

int	ft_wait(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(philo[i].thrd_id, NULL) != 0)
			return ((ft_printf(2, "pthread_join failed\n"), 0));
		i++;
	}
	return (1);
}
