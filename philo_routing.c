/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:35:34 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/19 17:05:46 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_message(1, philo, "has taken a fork");
	pthread_mutex_lock(philo->right_f);
	print_message(1, philo, "has taken a fork");
	print_message(1, philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_counter++;
	philo->time_of_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}
void	ode_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_message(1, philo, "has taken a fork");
	pthread_mutex_lock(philo->left_f);
	print_message(1, philo, "has taken a fork");
	print_message(1, philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->meals_counter++;
	philo->time_of_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}
void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		even_eating(philo);
	else
		ode_eating(philo);
}