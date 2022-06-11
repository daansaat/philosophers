/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:09 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 11:05:05 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

void	ft_error(t_data *data, char *str)
{
	printf("%s%s%s\n", RED, str, RESET);
	terminate_children(data);
	clean_up_sem(data);
	sem_close(data->done_eating_id);
	sem_close(data->death_id);
	exit(EXIT_FAILURE);
}

long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}	

int	ft_input_help(void)
{
	printf(" ____________________________________________________ \n");
	printf("|                                                    |\n");
	printf("|          Please enter 4 or 5 VALID arguments       |\n");
	printf("|____________________________________________________|\n");
	printf("|                                                    |\n");
	printf("|         [1][%sNumber of philosophers%s][2 - 500]       |\n", \
	PURPLE, RESET);
	printf("|         [2][%sTime to die%s][milliseconds]             |\n", \
	RED, RESET);
	printf("|         [3][%sTime to eat%s][milliseconds]             |\n", \
	GREEN, RESET);
	printf("|         [4][%sTime to sleep%s][milliseconds]           |\n", \
	YELLOW, RESET);
	printf("|      (( [5][%sNumber of meals%s][ > 0] ))              |\n", \
	TEAL, RESET);
	printf("|____________________________________________________|\n");
	printf("\n");
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long int	x;
	unsigned long int	i;
	unsigned long int	sign;

	x = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = x * 10 + str[i] - '0';
		i++;
	}
	return (x * sign);
}

int	ft_is_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
