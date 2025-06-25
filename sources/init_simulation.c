/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:57:16 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/25 13:58:20 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	allocate_simulation_resources(t_simulation *sim)
{
	sim->philosophers = malloc(sim->philo_count * sizeof(t_philosopher));
	if (!sim->philosophers)
		return (printf("Failed to allocate philosopher threads\n"), 1);
	sim->forks = malloc(sim->philo_count * sizeof(pthread_mutex_t));
	if (!sim->forks)
	{
		free(sim->philosophers);
		return (printf("Failed to allocate forks\n"), 1);
	}
	return (0);
}

void	initialize_mutexes(t_simulation *sim)
{
	size_t	i = 0;

	while (i < sim->philo_count)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
}

void	initialize_philosophers(t_simulation *sim)
{
	size_t	i = 0;

	while (i < sim->philo_count)
	{
		t_philosopher *philo = &sim->philosophers[i];
		
        philo->id = i + 1;
        philo->meals_eaten = 0;
        philo->sim = sim;
        philo->left_fork = &sim->forks[i];
        philo->right_fork = &sim->forks[(i + 1) % sim->philo_count];
        philo->last_meal_time = sim->start_time;
        i++;
	}
}

int	init_simulation(t_simulation *sim)
{
	if (allocate_simulation_resources(sim))
		return (1);
	initialize_mutexes(sim);
	sim->simulation_over = 0;
	sim->satisfied_philos = 0;
	sim->start_time = get_timestamp_ms();
	initialize_philosophers(sim);
	return (0);
}
