/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:07:55 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/11 15:08:07 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_putnbr_long(long nb, int *counter)
{
    if (nb < 0)
    {
        ft_putchar('-', counter);
        nb = -nb;
    }
    if (nb >= 10)
    {
        ft_putnbr_long(nb / 10, counter);
    }
    ft_putchar(nb % 10 + '0', counter);
}