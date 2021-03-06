/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:57 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/22 13:31:29 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static void	*death_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->mutex_id);
		if (ft_time() - data->time_last_meal > data->time_die)
		{
			printf("%s%ldms %sP%d has died\n%s", RESET, ft_time() - \
			data->time_start, RED, data->n + 1, RESET);
			exit(0);
		}
		sem_post(data->mutex_id);
	}
	return (0);
}

static void	print_state(char *str, char *color, t_data *data)
{
	long	time_ms;

	sem_wait(data->mutex_id);
	time_ms = ft_time() - data->time_start;
	printf("%s%ldms %sP%d %s\n%s", RESET, time_ms, color, data->n + 1, str, \
	RESET);
	data->time_now = ft_time();
	sem_post(data->mutex_id);
}

static void	eating(t_data *data)
{
	sem_wait(data->mutex_id);
	printf("%s%ldms %sP%d is eating\n%s", RESET, ft_time() - \
	data->time_start, GREEN, data->n + 1, RESET);
	data->time_last_meal = ft_time();
	data->meals -= 1;
	if (data->meals == 0)
		sem_post(data->done_eating_id);
	else
		sem_post(data->mutex_id);
	data->time_now = ft_time();
	usleep(data->time_eat * 500);
	while (ft_time() - data->time_now < data->time_eat)
		usleep(500);
}

void	ft_child_process(t_data *data)
{
	pthread_t	death;

	if (pthread_create(&death, NULL, &death_monitor, (void *)data) != 0)
		exit(-1);
	if (pthread_detach(death) != 0)
		exit(-1);
	while (1)
	{
		print_state("is thinking", PURPLE, data);
		sem_wait(data->can_sit_id);
		sem_wait(data->fork_id);
		print_state("has taken a fork", BLUE, data);
		sem_wait(data->fork_id);
		print_state("has taken a fork", BLUE, data);
		eating(data);
		sem_post(data->fork_id);
		sem_post(data->fork_id);
		sem_post(data->can_sit_id);
		print_state("is sleeping", YELLOW, data);
		usleep(data->time_sleep * 500);
		while (ft_time() - data->time_now < data->time_sleep)
			usleep(500);
	}
}
