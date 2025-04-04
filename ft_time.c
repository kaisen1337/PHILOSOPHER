/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:44 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/04 22:42:06 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// double	time_in_mcrs(int time_in_ms)
// {
// 	double	time_in_mcrs;

// 	time_in_mcrs = 0;
// 	time_in_mcrs = time_in_ms * 1000;
// 	return (time_in_mcrs);
// }
double time_in_mcrs(int time_in_ms)
{
    return time_in_ms * 1000.0;  // Use 1000.0 to force floating point arithmetic
}

double get_current_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);  // Use 1000.0 for floating point
}