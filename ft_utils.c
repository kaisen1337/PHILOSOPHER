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

void	print_message(int fd, t_philo *philo, char *str)
{
	long	current_time;

	current_time = 0;
	pthread_mutex_lock(&philo->data->print_mutex);
	check_if_alive(philo);
	current_time = (get_current_time()) - philo->data->start_time;
	ft_printf(fd, "%ld ", current_time);
	ft_printf(fd, " %d %s\n", philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
