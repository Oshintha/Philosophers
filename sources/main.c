/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:26:59 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/30 11:20:28 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_and_exit(t_simulation *sim, const char *error_msg)
{
	size_t	i;

	if (error_msg)
		printf("%s\n", error_msg);
	i = 0;
	while (i < sim->philo_count)
		pthread_mutex_destroy(&sim->forks[i++]);
	free(sim->philosophers);
	free(sim->forks);
	pthread_mutex_destroy(&sim->print_lock);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (validate_args(argc, argv, &sim))
		return (1);
	if (init_simulation(&sim))
		return (1);
	if (start_philosophers(&sim))
		return (1);
	stop_philosophers(&sim);
	if (join_philosophers(&sim))
		return (1);
	cleanup_and_exit(&sim, NULL);
	return (0);
}
