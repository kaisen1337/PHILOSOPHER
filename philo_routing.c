/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:35:34 by nkasimi           #+#    #+#             */
/*   Updated: 2025/07/02 08:23:23 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ode_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_counter++;
	philo->time_of_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

void	even_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_f);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_counter++;
	philo->time_of_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	eat(t_philo *philo)
{
	if (philo->data->num_of_philo == 1)
	{
		pthread_mutex_lock(philo->left_f);
		print_message(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_f);
	}
	else if (philo->id % 2 == 0)
		even_eating(philo);
	else
		ode_eating(philo);
}
