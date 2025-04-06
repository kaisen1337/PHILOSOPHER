/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:04:51 by nkasimi           #+#    #+#             */
/*   Updated: 2025/04/06 17:55:35 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_n;
	int					all_ate;
	double				start_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		check_mutex;
	pthread_mutex_t		meal_mutex;
	t_philo				*philo;
	int					stop;
	// int st;
}						t_data;

typedef struct s_philo
{
	int					meals_counter;
	double				time_of_last_meal;
	pthread_t			thrd_id;
	pthread_mutex_t		*left_f;
	pthread_mutex_t		*right_f;
	t_data				*data;
	int					id;
}						t_philo;

int						ft_printf(int fd, const char *str, ...);
int						ft_atoi(const char *nptr);
void					ft_putchar(int fd, char c, int *counter);

int						check_error(int ac, char **av, int *number);

int						ft_allocate(t_philo **philo, pthread_mutex_t **mutex,
							int number);
void					ft_free(t_philo **philo, pthread_mutex_t **mutex);
int						ft_wait(t_philo *philo, t_data *data);

double					get_current_time(void);

void					print_message(t_philo *philo, char *str);
void					eat(t_philo *philo);
void					*day_of_philo(void *test);

int						ft_init_data(t_data *data, char **av);
int						ft_init_philo(t_philo *philo, t_data *data,
							pthread_mutex_t *mutex);
int						ft_init_mutex(t_data *data, pthread_mutex_t *mutex);
int						ft_init(t_data *data, pthread_mutex_t *mutex,
							char **av);

int						check_meals(t_data *data);
int						check_death(t_data *data);
void					*ft_manager(void *arg);
void					*day_of_philo(void *arg);
#endif