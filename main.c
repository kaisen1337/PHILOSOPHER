/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/01 21:19:07 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	check_death(t_data *data)
{
	t_philo	*philos = data->philo;
	int		i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if ((get_current_time() - philos[i].time_of_last_meal) > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_lock(&data->print_mutex);
			ft_printf(1, "%ld %d died\n", get_current_time() - data->start_time, philos[i].id);
			data->stop = 1;
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

int	check_meals(t_data *data)
{
	t_philo	*philos = data->philo;
	int		i;
	int		full;

	i = 0;
	full = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->must_eat_n > 0 && philos[i].meals_counter >= data->must_eat_n)
			full++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (data->must_eat_n > 0 && full == data->num_of_philo)
	{
		pthread_mutex_lock(&data->print_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	*ft_manager(void *arg)
{
	t_data	*data = (t_data *)arg;

	while (!data->stop)
	{
		if (check_death(data) || check_meals(data))
			break;
		usleep(1000);
	}
	return (NULL);
}


void	*day_of_philo(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (!philo->data->stop)
	{
		eat(philo);
		if (philo->data->stop)
			break;
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->stop)
			break;
		print_message(philo, "is thinking");
	}
	return (NULL);
}



int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_data			data;
	pthread_t		manager_id;

	philo = NULL;
	mutex = NULL;
	if (!check_error(ac, av, &number_of_philo))
		return (1);
	if (!ft_allocate(&philo, &mutex, number_of_philo))
		return (1);
	if (!ft_init(&data, mutex, av))
		return (1);
	data.philo = philo;
    data.start_time = get_current_time();
	if (!ft_init_philo(philo, &data, mutex))
		return (1);
	if (pthread_create(&manager_id, NULL, ft_manager, &data) != 0)
		return (ft_printf(2, "pthread_create failed for monitor\n"), 1);
	if (!ft_wait(philo, &data))
		return (1);
	pthread_join(manager_id, NULL);
	ft_free(&philo, &mutex);
	return (0);
}
