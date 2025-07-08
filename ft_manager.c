/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:54:06 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/08 10:22:52 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	t_philo	*philos;
	double	df;
	int		i;

	philos = data->philo;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		df = (get_current_time() - philos[i].time_of_last_meal);
		pthread_mutex_unlock(&data->meal_lock);
		if (df > (double)data->time_to_die)
		{
			pthread_mutex_lock(&data->check_lock);
			data->stop = 1;
			pthread_mutex_unlock(&data->check_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", (long)(get_current_time()
					- data->start_time), (philos[i].id + 1));
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	check_meals_helper(t_data *data)
{
	pthread_mutex_lock(&data->check_lock);
	data->stop = 1;
	pthread_mutex_unlock(&data->check_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("All philosophers have eaten %d time\n", data->must_eat_n);
	pthread_mutex_unlock(&data->print_lock);
}

static int	check_meals(t_data *data)
{
	t_philo	*philos;
	int		i;
	int		flag;

	flag = 0;
	philos = data->philo;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->must_eat_n > 0 && philos[i].meals_counter >= data->must_eat_n)
			flag++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	if (data->must_eat_n > 0 && flag == data->num_of_philo)
	{
		check_meals_helper(data);
		return (1);
	}
	return (0);
}

void	*ft_manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_meals(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
