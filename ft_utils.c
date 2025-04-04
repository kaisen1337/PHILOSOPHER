/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:47:20 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/11 13:47:43 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	double	current_time;
	int		should_print;

	pthread_mutex_lock(&philo->data->check_mutex);
	should_print = !philo->data->stop;
	if (should_print)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		current_time = (get_current_time()) - philo->data->start_time;
		printf("%ld  %d %s\n", (long)(current_time), (philo->id + 1), str);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
}
