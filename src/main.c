/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:09:28 by paranha           #+#    #+#             */
/*   Updated: 2024/08/30 18:32:35 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *status)
{
	suseconds_t	ms;

	ms = timestamp() - philo->args->timestamp;
	pthread_mutex_lock(&philo->args->write);
	pthread_mutex_lock(&philo->args->simulator);
	if (philo->args->sim_running)
	{
		if (*status == *DEAD)
			philo->args->sim_running = false;
		printf("%ld %d %s\n", ms, philo->id, status);
	}
	pthread_mutex_unlock(&philo->args->simulator);
	pthread_mutex_unlock(&philo->args->write);
}

void	param_error(int param)
{
	if (param == 1)
		ft_putendl_fd("Error: Invalid number of philosophers", 2);
	if (param == 2)
		ft_putendl_fd("Error: Invalid time to die", 2);
	if (param == 3)
		ft_putendl_fd("Error: Invalid time to eat", 2);
	if (param == 4)
		ft_putendl_fd("Error: Invalid time to sleep", 2);
	if (param == 5)
		ft_putendl_fd("Error: Invalid number of meals", 2);
}

bool	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		return (false);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > MAX_PHI)
		return (param_error(1), false);
	if (ft_atoi(argv[2]) < 60)
		return (param_error(2), false);
	if (ft_atoi(argv[3]) < 60)
		return (param_error(3), false);
	if (ft_atoi(argv[4]) < 60)
		return (param_error(4), false);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (param_error(5), false);
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (EXIT_SUCCESS);
	return (true);
}

void	get_args(char **argv, t_args *args)
{
	args->num_phi = ft_atoi(argv[1]);
	args->ms_to_die = ft_atoi(argv[2]);
	args->ms_to_eat = ft_atoi(argv[3]);
	args->ms_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	philo[MAX_PHI];
	t_mutex	forks[MAX_PHI];

	if (!validate_args(argc, argv))
		return (EXIT_FAILURE);
	args = (t_args){0};
	get_args(argv, &args);
	start_simulation(&args, philo, forks);
	create_threads(philo);
	end_simulation(&args, philo, forks);
	return (EXIT_SUCCESS);
}
