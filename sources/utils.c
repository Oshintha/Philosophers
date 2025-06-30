/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:40:34 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/30 15:00:34 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_timestamp_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	custom_usleep(size_t ms, t_simulation *sim)
{
	size_t	start_time;
	size_t	i;

	i = 0;
	start_time = get_timestamp_ms();
	while ((get_timestamp_ms() - start_time) < ms)
	{
		if (i % 200 == 0)
		{
			pthread_mutex_lock(&sim->print_lock);
			if (sim->simulation_over)
			{
				pthread_mutex_unlock(&sim->print_lock);
				return (0);
			}
			pthread_mutex_unlock(&sim->print_lock);
		}
		usleep(500);
		i++;
	}
	return (1);
}

int	print_status(t_philosopher *philo, const char *message)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	if (philo->sim->simulation_over)
		return (pthread_mutex_unlock(&philo->sim->print_lock), 0);
	printf("%zu %d %s\n", get_timestamp_ms() - philo->sim->start_time,
		philo->id, message);
	return (pthread_mutex_unlock(&philo->sim->print_lock), 1);
}
