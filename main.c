/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/14 01:29:09 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	done_eating(t_philo *philo)
{
	if(philo->data->must_eat_n > 0 && philo->meals_counter >= philo->data->must_eat_n)
		return 0;
	return 1;
}

int check_if_alive(t_philo *philo)
{
    long time_passed;
    pthread_mutex_lock(&philo->data->check_mutex);
    time_passed = (get_current_time() - philo->time_of_last_meal) *1000;
    
    pthread_mutex_lock(&philo->data->print_mutex);
	ft_printf(" time to eat %d\n", philo->data->time_to_eat);
	ft_printf(" time to die %d\n", philo->data->time_to_die);
	ft_printf(" time passed %d\n",time_passed);
    pthread_mutex_unlock(&philo->data->print_mutex);
    if (time_passed > philo->data->time_to_die && !philo->data->stop)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d died\n", get_current_time() - philo->data->start_time, philo->id);
        philo->data->stop = 1;
        pthread_mutex_unlock(&philo->data->print_mutex);
        pthread_mutex_unlock(&philo->data->check_mutex);
        return 0;
    }
    
    if (philo->data->stop)
    {
        pthread_mutex_unlock(&philo->data->check_mutex);
        return 0;
    }
    
    pthread_mutex_unlock(&philo->data->check_mutex);
    return 1;
}

void	*day_of_philo(void *test)
{
	t_philo	*philo;
	philo = (t_philo *)test;
		philo->time_of_last_meal = get_current_time();
	while(1)
	{
		   if (!check_if_alive(philo) || !done_eating(philo))
            break;
		eat(philo);
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep);	
		print_message(philo, "is thinking");
	}
	return NULL;
}

void ft_init(t_philo *philo, t_data *data, pthread_mutex_t *mutex,  char **av)
{
	ft_initialize_data(data, av);
	ft_initialize_metux(data, mutex);
	ft_initialize_philo(philo, data, mutex);
	ft_wait(philo, data);
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
