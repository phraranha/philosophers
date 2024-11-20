/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:05:30 by paranha           #+#    #+#             */
/*   Updated: 2024/08/28 19:26:00 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHI 200
# define DEAD "died"
# define FORK_R "has taken a fork"
# define FORK_L "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	int					num_phi;
	suseconds_t			ms_to_die;
	suseconds_t			ms_to_eat;
	suseconds_t			ms_to_sleep;
	int					must_eat;
	t_mutex				write;
	t_mutex				simulator;
	suseconds_t			timestamp;
	bool				sim_running;
	pthread_t			god;
}						t_args;

typedef struct s_philo
{
	int					id;
	bool				sim_running;
	t_mutex				*l_fork;
	t_mutex				*r_fork;
	int					meals_eaten;
	suseconds_t			last_meal;
	pthread_t			thread;
	t_mutex				meal_mutex;
	t_args				*args;
}						t_philo;

void					ft_putendl_fd(char *s, int fd);
int						ft_atoi(const char *nptr);
t_mutex					*m_ternary(int condition, t_mutex *if_true,
							t_mutex *if_false);
suseconds_t				timestamp(void);
bool					sim_running(t_philo *philo);
void					start_simulation(t_args *args, t_philo *philos,
							t_mutex *forks);
void					end_simulation(t_args *args, t_philo *philos,
							t_mutex *forks);
void					create_threads(t_philo *philos);
void					*routine(void *philo);
void					*overseer(void *philos);
void					print_status(t_philo *philo, const char *status);
void					precise_usleep(suseconds_t ms);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
bool					full_belly(t_philo *philo);
void					precise_usleep(suseconds_t ms);

#endif
