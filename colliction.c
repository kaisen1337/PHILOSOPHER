
int	ft_initialize_data(t_data *data, char **av)
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
	data->start_time = 0;
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

int	ft_initialize_philo(t_philo *philo, t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i;
		philo->is_eating = 0;
		philo[i].meals_counter = 0;
		philo[i].time_of_last_meal = 0;
		philo[i].data = data;
		philo[i].left_f = &mutex[i];
		philo[i].right_f = &mutex[(i + 1) % data->num_of_philo];
		if (pthread_create(&philo[i].thrd_id, NULL, day_of_philo, &philo[i]) != 0)
			return ((ft_printf("pthread_creat failed\n"), 0));
		i++;
	}
	return (1);
}
void	ft_initialize_metux(t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	// exit((ft_printf("test%d", data->num_of_philo), 1));
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			while (i--)
				pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

int	ft_wait(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(philo[i].thrd_id, NULL) != 0)
			return ((ft_printf("pthread_join failed\n"), 0));
		i++;
	}
	return (1);
}

void	ft_free_main(t_philo *philo, void *mutex)
{
	free(mutex);
	free(philo);
}

int	ft_atoi(const char *nptr)
{
	long result;
	int sign;
	size_t i;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+')
	{
		i++;
	}
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

void	ft_putchar(char c, int *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

void	ft_putstr(char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar(*str, counter);
		str++;
	}
}

void	ft_putnbr(int nb, int *counter)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-', counter);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, counter);
	}
	ft_putchar(n % 10 + '0', counter);
}

void	format_specifier(va_list arguements, char specifier, int *counter)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(arguements, int), counter);
	else if (specifier == 's')
		ft_putstr((char *)va_arg(arguements, char *), counter);
}

int	ft_printf(const char *str, ...)
{
	va_list	arguements;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	va_start(arguements, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			format_specifier(arguements, str[i], &counter);
		}
		else
			ft_putchar(str[i], &counter);
		i++;
	}
	va_end(arguements);
	return (counter);
}
long	time_in_mcrs(int time_in_ms)
{
	long time_in_mcrs = 0;
	time_in_mcrs = time_in_ms * 1000;
	return (time_in_mcrs);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	ft_printf("%d %s\n", philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
void	even_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "hase taken  L fork");
	pthread_mutex_lock(philo->right_f);
	print_message(philo, "hase taken  R fork");
	print_message(philo, "is eating...");
	usleep(philo->data->time_to_eat);
	philo->meals_counter++;
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	print_message(philo, "is sleeping...");
}
void	ode_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	pthread_mutex_lock(philo->left_f);
	print_message(philo, "hase taken  R fork");
	print_message(philo, "hase taken  L fork");
	print_message(philo, "is eating...");
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	print_message(philo, "is sleeping...");
}
void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		even_eating(philo);
	else
		ode_eating(philo);
}
void	*day_of_philo(void *test)
{
	t_philo	*philo;

	philo = (t_philo *)test;
	ft_printf("%d ", philo->data->start_time);
	if (philo->id % 2 != 0)
	{
		// print_message(philo, "is sleeping😴");
		sleep(1);
	}
	print_message(philo, "is thinking");
	eat(philo);
	return (NULL);
}
void ft_init(t_philo *philo, t_data *data, pthread_mutex_t *mutex,  char **av)
{
	ft_initialize_data(data, av);
	ft_initialize_metux(data, mutex);
	ft_initialize_philo(philo, data, mutex);
	ft_wait(philo, data);
	ft_printf("meals counter %d\n", philo[0].meals_counter);
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
