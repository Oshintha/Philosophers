/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:34:37 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/25 13:59:08 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	size_t			meals_eaten;
	size_t			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_simulation	*sim;
}	t_philosopher;

typedef struct s_simulation
{
	size_t			philo_count;
	size_t			time_to_die_ms;
	size_t			time_to_eat_ms;
	size_t			time_to_sleep_ms;
	size_t			required_meals;
	size_t			satisfied_philos;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				simulation_over;
	size_t			start_time;
}	t_simulation;

// Argument Validation
int		validate_args(int argc, char **argv, t_simulation *sim);

// Initialization
int		init_simulation(t_simulation *sim);

// Philosopher Routine
void	*philosopher_routine(void *arg);

// Thread Management
int		start_philosophers(t_simulation *sim);
int		join_philosophers(t_simulation *sim);
void	stop_philosophers(t_simulation *sim);
int		should_simulation_stop(t_philosopher *philo);

// Utilities
int		print_status(t_philosopher *philo, const char *message);
size_t	get_timestamp_ms(void);
int		custom_usleep(size_t ms, t_simulation *sim);

//Clean
void	cleanup_and_exit(t_simulation *sim, const char *error_msg);
#endif
