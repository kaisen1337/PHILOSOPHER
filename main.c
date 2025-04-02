/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:20:38 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/02 23:09:45 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void print_message(t_philo *philo, char *str)
{
    long current_time;
    int should_print;

    // Check the stop flag with check_mutex
    pthread_mutex_lock(&philo->data->check_mutex);
    should_print = !philo->data->stop;
    pthread_mutex_unlock(&philo->data->check_mutex);

    if (should_print)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        current_time = (get_current_time()) - philo->data->start_time;
        printf("%ld  %d %s\n", current_time, philo->id, str);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}

// Updated check_death function
int check_death(t_data *data)
{
    t_philo *philos = data->philo;
    long time_since_last_meal;
	int i = 0;
    while (i < data->num_of_philo)
    {
        pthread_mutex_lock(&data->meal_mutex);
        time_since_last_meal = (get_current_time() - philos[i].time_of_last_meal);
		// time_since_last_meal -= data->delay;
		// printf(" ************time_since_last_meal %ld \n", time_since_last_meal);
        pthread_mutex_unlock(&data->meal_mutex);
        
        if (time_since_last_meal > data->time_to_die)
        {
            // Update stop flag with check_mutex
            pthread_mutex_lock(&data->check_mutex);
            data->stop = 1;
            pthread_mutex_unlock(&data->check_mutex);
            
            // Print the death message
            pthread_mutex_lock(&data->print_mutex);
            printf("%ld %d died\n", get_current_time() - data->start_time, philos[i].id);
            pthread_mutex_unlock(&data->print_mutex);
            
            return (1);
        }
        i++;
    }
    return (0);
}

// Updated check_meals function
int check_meals(t_data *data)
{
    t_philo *philos = data->philo;
    int i;
    int full;

    i = 0;
    full = 0;
    while (i < data->num_of_philo)
    {
        pthread_mutex_lock(&data->meal_mutex); // Use meal_mutex for meal counts
        if (data->must_eat_n > 0 && philos[i].meals_counter >= data->must_eat_n)
            full++;
        pthread_mutex_unlock(&data->meal_mutex);
        i++;
    }
    
    if (data->must_eat_n > 0 && full == data->num_of_philo)
    {
        // Update stop flag with check_mutex
        pthread_mutex_lock(&data->check_mutex);
        data->stop = 1;
        pthread_mutex_unlock(&data->check_mutex);
        return (1);
    }
    return (0);
}

// Updated ft_manager function
void *ft_manager(void *arg)
{
    t_data *data = (t_data *)arg;
    int should_continue;
    while (1)
    {
        // Check stop flag with check_mutex
        pthread_mutex_lock(&data->check_mutex);
        should_continue = !data->stop;
        pthread_mutex_unlock(&data->check_mutex);
        
        if (!should_continue)
            break;
            
        if (check_death(data) || check_meals(data))
            break;
        usleep(2000);
    }
    return (NULL);
}

// Updated day_of_philo function
void *day_of_philo(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int should_exit;

    while (1)
    {
        // Check stop flag with check_mutex
        pthread_mutex_lock(&philo->data->check_mutex);
        should_exit = philo->data->stop;
		// printf("%d\n delay ", philo->data->delay);
		// philo->data->delay +=1; 
        pthread_mutex_unlock(&philo->data->check_mutex);
        
        if (should_exit)
            break;
        eat(philo);
        print_message(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        print_message(philo, "is thinking");
    }
    return (NULL);
}
int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_data			data;
	pthread_t		manager_id;

	philo = NULL;
	mutex = NULL;
	if (!check_error(ac, av, &number_of_philo))
		return (1);
	if (!ft_allocate(&philo, &mutex, number_of_philo))
		return (1);
	if (!ft_init(&data, mutex, av))
		return (1);
	data.philo = philo;
    data.start_time = get_current_time();
	if (!ft_init_philo(philo, &data, mutex))
		return (1);
	if (pthread_create(&manager_id, NULL, ft_manager, &data) != 0)
		return (ft_printf(2, "pthread_create failed for monitor\n"), 1);
	if (!ft_wait(philo, &data))
		return (1);
	pthread_join(manager_id, NULL);
	ft_free(&philo, &mutex);
	return (0);
}
