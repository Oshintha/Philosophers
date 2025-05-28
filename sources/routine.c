/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:39:47 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/26 20:39:47 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	grab_forks(t_philosopher *philo)
{
	if (should_simulation_stop(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork), 0);
	if (should_simulation_stop(philo) || philo->sim->philo_count == 1)
		return (pthread_mutex_unlock(philo->left_fork), 0);
	pthread_mutex_lock(philo->right_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), 0);
	return (1);
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	philo->meals_eaten++;
	philo->last_meal_time = get_timestamp_ms();
	pthread_mutex_unlock(&philo->sim->print_lock);

	print_status(philo, "is eating");
	custom_usleep(philo->sim->time_to_eat_ms, philo->sim);

	pthread_mutex_lock(&philo->sim->print_lock);
	if (philo->sim->required_meals &&
		philo->meals_eaten == philo->sim->required_meals)
		philo->sim->satisfied_philos++;
	pthread_mutex_unlock(&philo->sim->print_lock);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	sleep_and_think(t_philosopher *philo)
{
	if (!print_status(philo, "is sleeping"))
		return (0);
	if (!custom_usleep(philo->sim->time_to_sleep_ms, philo->sim))
		return (0);
	if (!print_status(philo, "is thinking"))
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		custom_usleep(10, philo->sim);
	while (1)
	{
		if (!grab_forks(philo))
			break;
		eat(philo);
		if (!sleep_and_think(philo))
			break;
	}
	return (NULL);
}
