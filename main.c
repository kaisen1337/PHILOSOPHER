/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/08 10:28:13 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*day_of_philo(void *arg)
{
	t_philo	*philo;
	int		should_exit;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 && philo->data->num_of_philo != 1)
	{
		print_message(philo, "is thinking");
		usleep(philo->data->time_to_eat * 1000);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->check_lock);
		should_exit = philo->data->stop;
		pthread_mutex_unlock(&philo->data->check_lock);
		if (should_exit)
			break ;
		eat(philo);
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->num_of_philo % 2 != 0)
			usleep(1000);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

static int	manager(t_philo **philo, t_data *data, pthread_mutex_t **lock,
		pthread_t *manager_id)
{
	if (pthread_create(manager_id, NULL, ft_manager, data) != 0)
	{
		pthread_mutex_lock(&data->check_lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->check_lock);
		ft_wait(*philo, data);
		ft_free(philo, lock);
		return (ft_printf(2, "pthread_create failed for manager\n"), 0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*lock;
	t_data			data;
	pthread_t		manager_id;

	philo = NULL;
	lock = NULL;
	if (!check_error(ac, av, &number_of_philo) || !ft_allocate(&philo, &lock,
			number_of_philo))
		return (1);
	if (!ft_init(&data, lock, av))
		return ((ft_free(&philo, &lock), 1));
	data.philo = philo;
	data.start_time = get_current_time();
	if (!ft_init_philo(philo, &data, lock))
		return ((ft_free(&philo, &lock), 1));
	if (!manager(&philo, &data, &lock, &manager_id))
		return (1);
	if (!ft_wait(philo, &data))
		return (1);
	pthread_join(manager_id, NULL);
	ft_free(&philo, &lock);
	return (0);
}
