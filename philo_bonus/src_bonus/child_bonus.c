#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

static void	sleeping(t_data *data)
{
	print_state("is sleeping", YELLOW, data);
	usleep(data->time_sleep);
	print_state("is thinking", PURPLE, data);
}

static void	eating(t_data *data)
{
	data->time_last_meal = ft_time();
	if (data->meals > 0)
		data->meals -= 1;
	if (data->meals == 0 && !data->done_eating)
	{
		data->done_eating = 1;
		sem_wait(data->print_id);
		printf("%ldms %sP%d is eating final\n%s", ft_time() - \
		data->time_start, GREEN, data->n + 1, RESET);
		sem_post(data->meals_id);
		sem_wait(data->done_eating_id);
		sem_post(data->print_id);
	}
	else
    	print_state("is eating", GREEN, data);
	usleep(data->time_eat);
}

static void	take_forks(t_data *data)
{
    if (sem_wait(data->fork_id) < 0)
        ft_error(data, "sem_wait() failed");
	print_state("has taken a fork", BLUE, data);
    if (sem_wait(data->fork_id) < 0)
        ft_error(data, "sem_wait() failed\n");
	print_state("has taken a fork", BLUE, data);
	eating(data);
    if (sem_post(data->fork_id) < 0)
        ft_error(data, "sem_post() failed\n");
    if (sem_post(data->fork_id) < 0)
        ft_error(data, "sem_post() failed\n");
}

static void*	death_monitor(void *arg)
{
	t_data	*data;
	long	time;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->print_id);
		time = ft_time();
		if (data->time_last_meal - data->time_start > data->time_die)
		{
			printf("%ldms %sP%d has died\n%s", time - \
			data->time_start, RED, data->n + 1, RESET);
			sem_post(data->death_id);
			break ;
		}
		sem_post(data->print_id);
	}
	return (0);
}

void    ft_child_process(t_data *data)
{
    pthread_t	death;

	pthread_create(&death, NULL, &death_monitor, (void*)data);
	pthread_detach(death);
    while (1)
    {
        take_forks(data);
        sleeping(data);
    }
}
