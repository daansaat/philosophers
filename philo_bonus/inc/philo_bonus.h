/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/12 11:15:48 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define TEAL "\033[0;36m"
# define RESET "\033[0m"

typedef struct s_data
{
	int		p;
	int		n;
	int		meals;
	long	time_start;
	long	time_last_meal;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	time_now;
	pid_t	*pid_child;
	sem_t	*fork_id;
	sem_t	*can_sit_id;
	sem_t	*mutex_id;
	sem_t	*done_eating_id;
}				t_data;

void	init_semaphore(t_data *data);
void	init_processes(t_data *data);

void	ft_parent_process(t_data *data);
void	ft_child_process(t_data *data);
void	ft_stop(t_data *data);

void	ft_error(t_data *data, char *str);
long	ft_atol(const char *str, long max);
long	ft_time(void);
int		ft_input_help(void);

#endif