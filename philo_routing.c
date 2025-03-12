/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:35:34 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/12 13:09:14 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "hase taken  L fork");
	pthread_mutex_lock(philo->right_f);
	print_message(philo, "hase taken  R fork");
	print_message(philo, "is eating...");
	usleep(philo->data->time_to_eat *1000);
	philo->meals_counter++;
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	print_message(philo, "is sleeping...");
	// usleep(philo->data->time_to_eat);
}
void	ode_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "hase taken  R fork");
	print_message(philo, "hase taken  L fork");
	print_message(philo, "is eating...");
	usleep(philo->data->time_to_eat *1000);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	print_message(philo, "is sleeping...");
	// usleep(philo->data->time_to_eat);
}
void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		even_eating(philo);
	else
		ode_eating(philo);
}