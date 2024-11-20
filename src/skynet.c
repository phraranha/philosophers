/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skynet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:20:44 by paranha           #+#    #+#             */
/*   Updated: 2024/08/30 18:09:15 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(suseconds_t ms)
{
	suseconds_t	start;

	start = timestamp();
	while (timestamp() - start < ms)
		usleep(250);
}

bool	full_belly(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->meal_mutex);
	status = (philo->args->must_eat == philo->meals_eaten);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (status);
}

void	*routine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	while (sim_running(phi) && !full_belly(phi))
	{
		eating(phi);
		sleeping(phi);
		thinking(phi);
	}
	return (NULL);
}

bool	flatline(t_philo *philo, int *meals)
{
	bool	dead;

	pthread_mutex_lock(&philo->meal_mutex);
	dead = (timestamp() - philo->last_meal > philo->args->ms_to_die);
	if (!dead)
		*meals += philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (dead)
		print_status(philo, DEAD);
	return (dead);
}

void	*overseer(void *philos)
{
	t_philo	*phi;
	int		meals;
	int		i;

	phi = (t_philo *)philos;
	while (sim_running(phi))
	{
		meals = 0;
		i = 0;
		while (i < phi->args->num_phi)
		{
			if (flatline(&phi[i++], &meals))
				return (NULL);
		}
		if (meals == phi->args->num_phi * phi->args->must_eat)
			break ;
	}
	return (NULL);
}
