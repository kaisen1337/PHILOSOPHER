/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisen1337 <kaisen1337@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:47:20 by nkasimi           #+#    #+#             */
/*   Updated: 2025/06/28 06:45:32 by kaisen1337       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	double	current_time;
	int		should_print;

	pthread_mutex_lock(&philo->data->check_lock);
	should_print = !philo->data->stop;
	if (should_print)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		current_time = (get_current_time()) - philo->data->start_time;
		printf("%ld  %d %s\n", (long)(current_time), (philo->id + 1), str);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->check_lock);
}

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000.0) + (time.tv_usec / 1000.0));
}
