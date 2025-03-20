/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/20 12:35:45 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	done_eating(t_philo *philo)
{
	if (philo->data->must_eat_n > 0
		&& philo->meals_counter >= philo->data->must_eat_n)
		return (0);
	return (1);
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
	usleep(1000);
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


int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_data			data;
	// t_philo	*manager;
	philo = NULL;
	mutex = NULL;
	if (check_error(ac, av, &number_of_philo) == -1)
		return (1);
	if (ft_allocate(&philo, &mutex, number_of_philo) == -1)
		return (1);
	if(!ft_init(philo, &data, mutex, av))
		
		return (1);
	return (0);
}
