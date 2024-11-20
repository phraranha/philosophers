/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:16:37 by paranha           #+#    #+#             */
/*   Updated: 2024/08/30 18:10:14 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	start_simulation(t_args *args, t_philo *philos, t_mutex *forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&args->write, NULL);
	pthread_mutex_init(&args->simulator, NULL);
	args->sim_running = true;
	args->timestamp = timestamp();
	while (i < args->num_phi)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].sim_running = true;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		pthread_mutex_init(&forks[i], NULL);
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = m_ternary(i == args->num_phi - 1, &forks[0], &forks[i
				+ 1]);
		philos[i].args = args;
		philos[i].last_meal = args->timestamp;
		i++;
	}
}

void	end_simulation(t_args *args, t_philo *philos, t_mutex *forks)
{
	int	i;

	i = 0;
	while (i < args->num_phi)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		pthread_mutex_destroy(&forks[i++]);
	}
	pthread_mutex_destroy(&args->write);
	pthread_mutex_destroy(&args->simulator);
}

bool	sim_running(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->args->simulator);
	status = philo->args->sim_running;
	pthread_mutex_unlock(&philo->args->simulator);
	return (status);
}

void	create_threads(t_philo *philos)
{
	int	i;

	pthread_create(&philos->args->god, NULL, overseer, philos);
	i = 0;
	while (i < philos->args->num_phi)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		usleep(500);
		i++;
	}
	pthread_join(philos->args->god, NULL);
	i = 0;
	while (i < philos->args->num_phi)
		pthread_join(philos[i++].thread, NULL);
}
