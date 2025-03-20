int	ft_init_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = time_in_mcrs(ft_atoi(av[2]));
	data->time_to_eat = time_in_mcrs(ft_atoi(av[3]));
	data->time_to_sleep = time_in_mcrs(ft_atoi(av[4]));
	if (av[5])
		data->must_eat_n = ft_atoi(av[5]);
	else
		data->must_eat_n = -1;
	data->all_ate = 0;
	data->stop = 0;
	data->start_time = get_current_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->check_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->check_mutex);
		return (0);
	}
	return (1);
}

int	ft_init_philo(t_philo *philo, t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i;
		philo[i].is_eating = 0;
		philo[i].meals_counter = 0;
		philo[i].time_of_last_meal = get_current_time();
		philo[i].data = data;
		philo[i].left_f = &mutex[i];
		philo[i].right_f = &mutex[(i + 1) % data->num_of_philo];
		if (pthread_create(&philo[i].thrd_id, NULL, day_of_philo,
				&philo[i]) != 0)
			return ((ft_printf(2, "pthread_creat failed\n"), 0));
		i++;
	}
	return (1);
}
int	ft_init_mutex(t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&mutex[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int 	ft_init(t_philo *philo, t_data *data, pthread_mutex_t *mutex, char **av)
{
	if(!ft_init_data(data, av))
		return 0;
	if(!ft_init_mutex(data, mutex))
		return 0;
	if(!ft_init_philo(philo, data, mutex))
		return 0;
	if(!ft_wait(philo, data))
		return 0;
	ft_free(&philo, &mutex);
	return 1;
}

int	ft_wait(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(philo[i].thrd_id, NULL) != 0)
			return ((ft_printf(2, "pthread_join failed\n"), 0));
		i++;
	}
	return (1);
}
void	print_message(int fd, t_philo *philo, char *str
{
	long	current_time;

	current_time = 0;
	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = (get_current_time()) - philo->data->start_time;
	ft_printf(fd, "%ld ", current_time);
	ft_printf(fd, " %d %s\n", philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
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
int	done_eating(t_philo *philo)
{
	if (philo->data->must_eat_n > 0
		&& philo->meals_counter >= philo->data->must_eat_n)
		return (0);
	return (1);
}

int	check_if_alive(t_philo *philo)
{
	long	time_passed;

	pthread_mutex_lock(&philo->data->check_mutex);
	time_passed = (get_current_time() - philo->time_of_last_meal) * 1000;
	if (time_passed > philo->data->time_to_die && !philo->data->stop)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		ft_printf(1, "*********************************%ld %d died\n",
			get_current_time() - philo->data->start_time, philo->id);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->check_mutex);
		return (0);
	}
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->check_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
	return (1);
}

void	*day_of_philo(void *test)
{
	t_philo	*philo;

	philo = (t_philo *)test;
	philo->time_of_last_meal = get_current_time();
	while (1)
	{
		if (!check_if_alive(philo) || !done_eating(philo))
			break ;
		eat(philo);
		print_message(1, philo, "is sleeping");
		usleep(philo->data->time_to_sleep);
		print_message(1, philo, "is thinking");
	}
	return (NULL);
}

void	ft_init(t_philo *philo, t_data *data, pthread_mutex_t *mutex, char **av)
{
	ft_init_data(data, av);
	ft_init_mutex(data, mutex);
	ft_init_philo(philo, data, mutex);
	ft_wait(philo, data);
	ft_free(&philo, &mutex);
}

int	main(int ac, char **av)
{
	int				number_of_philo;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_data			data;

	philo = NULL;
	mutex = NULL;
	if (check_error(ac, av, &number_of_philo) == 1)
		return (1);
	if (ft_allocate(&philo, &mutex, number_of_philo) == -1)
		return (1);
	ft_init(philo, &data, mutex, av);
	return (0);
}
