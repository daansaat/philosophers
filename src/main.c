#include "philo.h"
#include <stdlib.h>

static void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	free(data->forks);
	free(data->philo);
}

static int	parse_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (ft_is_digit(argv))
		return (ft_input_help());
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 2000)
		return (ft_input_help());
	if (argv[5])
		if (ft_atoi(argv[5]) <= 0)
			return (ft_input_help());
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (parse_input(argc, argv))
		return (1);
	if (init_struct(argv, &data))
		return (1);
	if (init_mutex(&data))
		return (1);
	if (init_monitor(&data) || init_threads(&data))
		return (1);
	free_and_destroy(&data);
	return (0);
}