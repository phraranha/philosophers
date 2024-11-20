/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_and_sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:44 by paranha           #+#    #+#             */
/*   Updated: 2024/08/30 18:08:55 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_phi(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, FORK_R);
	precise_usleep(philo->args->ms_to_die + 11);
	pthread_mutex_unlock(philo->l_fork);
}

void	hands(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, FORK_R);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_L);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK_L);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, FORK_R);
	}
}

void	eating(t_philo *philo)
{
	if (philo->args->num_phi == 1)
		return (one_phi(philo));
	hands(philo);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_usleep(philo->args->ms_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->args->ms_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, THINKING);
	precise_usleep((philo->args->ms_to_die - philo->args->ms_to_eat
			- philo->args->ms_to_sleep) - 100);
}
