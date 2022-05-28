#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	init_philo(char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		data->philo[i].n = i;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->p;
		data->philo[i].meals = -1;
		if (argv[5])
			data->philo[i].meals = ft_atoi(argv[5]);
		data->philo[i].time_last_meal = data->time_start;
		data->philo[i].data = data;
		i++;
	}
}

int	init_struct(char **argv, t_data *data)
{
	data->p = ft_atoi(argv[1]);
	data->threads = malloc(sizeof(pthread_t) * data->p);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	if (!data->threads || !data->monitor || !data->forks || !data->philo)
		return (1);
	data->time_start = ft_time();
	data->has_died = 0;
	data->done_eating = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	init_philo(argv, data);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Failed to initialize fork mutex");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		printf("Failed to initialize print mutex");
		return (1);
	}
	if (pthread_mutex_init(&data->meals_monitor, NULL) != 0)
	{
		printf("Failed to initialize meals_monitor mutex");
		return (1);
	}
	return (0);
}	

int	init_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &death_monitor, \
	(void*)data) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	if (pthread_detach(data->monitor) != 0)
	{
		printf("Failed to detach monitor thread\n");
		return (1);
	}
	return (0);
}

int	init_threads(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->p)
	{
		if (pthread_create(&data->threads[i], NULL, &dining, \
		(void*)&data->philo[i]) != 0)
		{
			printf("Failed to create thread P%d\n", i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->p)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
		{
			printf("Failed to join thread P%d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}