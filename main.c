/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/01 11:29:32 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	done_eating(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->must_eat_n > 0
		&& philo->meals_counter >= philo->data->must_eat_n)
		result = 0;
	else
		result = 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (result);
}

int	check_if_alive(t_philo *philo)
{
	long	time_passed;

	pthread_mutex_lock(&philo->data->check_mutex);
	time_passed = (get_current_time() - philo->time_of_last_meal) * 1000;
	if (time_passed > philo->data->time_to_die && !philo->data->stop)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf(1, "*********************************%ld %d died\n",
			get_current_time() - philo->data->start_time, philo->id);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->check_mutex);
		return (0);
	}
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->check_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
	return (1);
}

void	*day_of_philo(void *test)
{
	t_philo	*philo;

	philo = (t_philo *)test;
	philo->time_of_last_meal = get_current_time();
	while (1)
	{
		if (!check_if_alive(philo) || !done_eating(philo))
			break ;
		eat(philo);
		print_message(1, philo, "is sleeping");
		usleep(philo->data->time_to_sleep);
		print_message(1, philo, "is thinking");
	}
	return (NULL);
}
// Function to check if a philosopher has died
int	check_philosopher_death(t_data *data, t_philo *philos, int i)
{
	long	time_passed;

	pthread_mutex_lock(&data->meal_mutex);
	time_passed = (get_current_time() - philos[i].time_of_last_meal) * 1000;
	pthread_mutex_unlock(&data->meal_mutex);
	pthread_mutex_lock(&data->check_mutex);
	if (time_passed > data->time_to_die && !data->stop)
	{
		pthread_mutex_lock(&data->print_mutex);
		ft_printf(1, "%ld %d died\n", get_current_time() - data->start_time,
			philos[i].id + 1);
		data->stop = 1;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->check_mutex);
	return (0);
}

// Function to check if all philosophers have eaten enough
int	check_all_ate(t_data *data, t_philo *philos)
{
	int	all_ate;
	int	i;

	all_ate = 1;
	i = 0;
	if (data->must_eat_n <= 0)
		return (0);
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (philos[i].meals_counter < data->must_eat_n)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->check_mutex);
		data->all_ate = 1;
		data->stop = 1;
		pthread_mutex_unlock(&data->check_mutex);
		return (1);
	}
	return (0);
}

// Main monitoring function
void	*ft_manager(void *arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;

	data = (t_data *)arg;
	philos = (t_philo *)data->philo;
	usleep(1000);
	while (!data->stop)
	{
		i = 0;
		while (i < data->num_of_philo && !data->stop)
		{
			if (check_philosopher_death(data, philos, i))
				break ;
			i++;
			usleep(100);
		}
		if (!data->stop && check_all_ate(data, philos))
			break ;
		usleep(500);
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
