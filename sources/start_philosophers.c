/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:09:17 by aoshinth          #+#    #+#             */
/*   Updated: 2025/05/24 22:09:17 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_philosopher_thread(t_simulation *sim, size_t i)
{
	if (pthread_create(&(sim->philosophers[i].thread), NULL,
			&philosopher_routine, &sim->philosophers[i]) != 0)
		return (cleanup_and_exit(sim, "Error while creating threads"), 1);
	return (0);
}

int	join_philosopher_thread(t_simulation *sim, size_t i)
{
	if (pthread_join(sim->philosophers[i].thread, NULL) != 0)
		return (cleanup_and_exit(sim, "Error while joining threads"), 1);
	return (0);
}

int	start_philosophers(t_simulation *sim)
{
	size_t	i = 0;

	while (i < sim->philo_count)
	{
		if (create_philosopher_thread(sim, i++))
			return (1);
	}
	return (0);
}

int	join_philosophers(t_simulation *sim)
{
	size_t	i = 0;

	while (i < sim->philo_count)
	{
		if (join_philosopher_thread(sim, i++))
			return (1);
	}
	return (0);
}
