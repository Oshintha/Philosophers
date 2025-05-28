/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:32:14 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/26 19:32:14 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_simulation_end(t_simulation *sim)
{
	size_t	i = 0;

	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->print_lock);
		if ((get_timestamp_ms() - sim->philosophers[i].last_meal_time >= sim->time_to_die_ms)
			|| sim->satisfied_philos == sim->philo_count)
		{
			sim->simulation_over = 1;
			if (sim->satisfied_philos == sim->philo_count)
				printf("Every philosopher ate %zu times\n", sim->required_meals);
			else
				printf("%zu %d died\n", get_timestamp_ms() - sim->start_time, (int)(i + 1));
			pthread_mutex_unlock(&sim->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&sim->print_lock);
		i++;
	}
	return (0);
}

void	stop_philosophers(t_simulation *sim)
{
	while (1)
	{
		if (check_simulation_end(sim))
			break;
	}
}

int	should_simulation_stop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	if (philo->sim->simulation_over)
	{
		pthread_mutex_unlock(&philo->sim->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->print_lock);
	return (0);
}
