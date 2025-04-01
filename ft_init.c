/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:44:20 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/01 11:26:50 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = time_in_mcrs(ft_atoi(av[2]));
	data->time_to_eat = time_in_mcrs(ft_atoi(av[3]));
	data->time_to_sleep = time_in_mcrs(ft_atoi(av[4]));
	if (av[5])
		data->must_eat_n = ft_atoi(av[5]);
	else
		data->must_eat_n = -1;
	data->all_ate = 0;
	data->stop = 0;
	data->start_time = get_current_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->check_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->check_mutex);
		return (0);
	}
	return (1);
}

int	ft_init_philo(t_philo *philo, t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i+1;
		philo[i].is_eating = 0;
		philo[i].meals_counter = 0;
		philo[i].time_of_last_meal = get_current_time();
		philo[i].data = data;
		philo[i].left_f = &mutex[i];
		philo[i].right_f = &mutex[(i + 1) % data->num_of_philo];
		if (pthread_create(&philo[i].thrd_id, NULL, day_of_philo,
				&philo[i]) != 0)
			return ((ft_printf(2, "pthread_creat failed\n"), 0));
		i++;
	}
	return (1);
}
int	ft_init_mutex(t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&mutex[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_init(t_data *data, pthread_mutex_t *mutex, char **av)
{
	if (!ft_init_data(data, av))
		return (0);
	if (!ft_init_mutex(data, mutex))
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
