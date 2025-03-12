/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:04:51 by nkasimi           #+#    #+#             */
/*   Updated: 2025/03/11 15:11:37 by nkasimi          ###   ########.fr       */
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

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_n;
	int				all_ate;
	int				stop;
	long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	meal_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				is_eating;
	int				meals_counter;
	long long		time_of_last_meal;
	pthread_t		thrd_id;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_data			*data;
}					t_philo;
void	ft_putchar(char c, int *counter);
void ft_putnbr_long(long nb, int *counter);
int					ft_printf(const char *str, ...);
int					ft_atoi(const char *nptr);

void				ode_eating(t_philo *philo);
void				even_eating(t_philo *philo);
void				eat(t_philo *philo);
void				print_message(t_philo *philo, char *str);

int					check_error(int ac, char **av, int *number);

int	ft_initialize_data(t_data *data, char **av);
int	ft_initialize_philo(t_philo *philo, t_data *data, pthread_mutex_t *mutex);
void	ft_initialize_metux(t_data *data, pthread_mutex_t *mutex);
int	ft_wait(t_philo *philo, t_data *data);
void	ft_free_main(t_philo *philo, void *mutex);

void				*day_of_philo(void *test);

void				creat_philo(t_philo *philo, int index);
int					ft_wait(t_philo *philo, t_data *data);

void				set_mutex(t_philo *philo, pthread_mutex_t *resource,
						int num);
void				destroy_mutex(pthread_mutex_t *mutex, int num);
long				time_in_mcrs(int time_in_ms);
long	get_current_time(void);
#endif