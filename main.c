/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/12 13:18:55 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*day_of_philo(void *test)
{
	t_philo	*philo;

	philo = (t_philo *)test;
	while(1)
	{
		print_message(philo, "is thinking");
		eat(philo);
	}
	return (NULL);
}
void ft_init(t_philo *philo, t_data *data, pthread_mutex_t *mutex,  char **av)
{
	ft_initialize_data(data, av);
	ft_initialize_metux(data, mutex);
	ft_initialize_philo(philo, data, mutex);
	ft_wait(philo, data);
	ft_printf("meals counter %d\n", philo[0].meals_counter);
	ft_free_main(philo, mutex);
}
int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_data			data;

	if (check_error(ac, av, &number_of_philo) == 1)
		return (1);
	philo = malloc(sizeof(t_philo) * number_of_philo);
	if (!philo)
		return (1);
	mutex = malloc(sizeof(pthread_mutex_t) * number_of_philo);
	if (!mutex)
		return (1);

	ft_init(philo, &data, mutex, av);
	return (0);
}
