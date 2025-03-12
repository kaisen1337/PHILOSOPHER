/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:44 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/11 14:10:55 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_in_mcrs(int time_in_ms)
{
	long time_in_mcrs = 0;
	time_in_mcrs = time_in_ms * 1000;
	return (time_in_mcrs);
}
long	get_current_time(void)
{
	long current_time;
	struct timeval time;
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) +(time.tv_usec / 1000);
	return current_time;
}