/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:54:06 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/04 22:52:21 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	t_philo	*philos;
	double	time_since_last_meal;
	int		i;

	philos = data->philo;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		time_since_last_meal = (get_current_time()
				- philos[i].time_of_last_meal);
		pthread_mutex_unlock(&data->meal_mutex);
		if (time_since_last_meal >(double) data->time_to_die)
		{
		printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55 %f\n", time_since_last_meal);
			pthread_mutex_lock(&data->check_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->check_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", (long)(get_current_time() - data->start_time),
				(philos[i].id + 1));
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meals(t_data *data)
{
	t_philo	*philos;
	int		i;
	int		full;

	philos = data->philo;
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
		pthread_mutex_lock(&data->check_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->check_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%f All philosophers have eaten enough\n", get_current_time()
			- data->start_time);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

// Updated ft_manager function
void	*ft_manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	// int should_continue ;
	while (1)
	{
		if (check_death(data) || check_meals(data))
			break ;
		usleep(100);
	}
	return (NULL);
}

// void *day_of_philo(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//     int should_exit;
//     if (philo->id % 2 != 0)
//     {
//         print_message(philo, "is thinking");
//         usleep(1000);
//         // usleep(philo->data->time_to_eat * 1000);
//     }
//     while (1)
//     {
//         pthread_mutex_lock(&philo->data->check_mutex);
//         should_exit = philo->data->stop;
//         pthread_mutex_unlock(&philo->data->check_mutex);
//         if (should_exit)
//             break ;
//         eat(philo);
//         print_message(philo, "is sleeping");
//         usleep(philo->data->time_to_sleep * 1000);
//         print_message(philo, "is thinking");
//     }
//     return (NULL);
// }
// int	main(int ac, char **av)
// {
// 	int				number_of_philo;
// 	t_philo			*philo;
// 	pthread_mutex_t	*mutex;
// 	t_data			data;
// 	pthread_t		manager_id;

// 	philo = NULL;
// 	mutex = NULL;
// 	if (!check_error(ac, av, &number_of_philo))
// 		return (1);
// 	if (!ft_allocate(&philo, &mutex, number_of_philo))
// 		return (1);
// 	if (!ft_init(&data, mutex, av))
// 		return (1);
// 	data.philo = philo;
//     data.start_time = get_current_time();
// 	if (!ft_init_philo(philo, &data, mutex))
// 		return (1);
// 	if (pthread_create(&manager_id, NULL, ft_manager, &data) != 0)
// 		return (ft_printf(2, "pthread_create failed for monitor\n"), 1);
// 	if (!ft_wait(philo, &data))
// 		return (1);
// 	pthread_join(manager_id, NULL);
// 	ft_free(&philo, &mutex);
// 	return (0);
// }
/* Improved Dining Philosophers Implementation */

/* Thread function for each philosopher */
/* Improved Dining Philosophers Implementation for odd numbers */
