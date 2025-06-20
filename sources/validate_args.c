/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:14:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/06/20 00:35:26 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_usage_and_exit(void)
{
	printf("Usage: ./philo arg1 arg2 arg3 arg4 [arg5]\n");
	printf("Arg#    Name                        			Type        Range\n");
	printf("arg1    number_of_philosophers      			mandatory   > 0\n");
	printf("arg2    time_to_die (ms)            			mandatory   > 0\n");
	printf("arg3    time_to_eat (ms)            			mandatory   > 0\n");
	printf("arg4    time_to_sleep (ms)          			mandatory   > 0\n");
	printf("arg5    number_of_times_each_philosopher_must_eat	optional    > 0\n");
	exit(1);
}

int	parse_positive_int(const char *str, size_t *num)
{
	size_t	res = 0;

	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	if (*str || res == 0)
		return (print_usage_and_exit(), 1);
	*num = res;
	return (0);
}

int	validate_args(int argc, char **argv, t_simulation *sim)
{
	if (argc < 5 || argc > 6)
		return(print_usage_and_exit(), 1);
	if (parse_positive_int(argv[1], &sim->philo_count))
		return (print_usage_and_exit(), 1);
	if (parse_positive_int(argv[2], &sim->time_to_die_ms))
		return (print_usage_and_exit(), 1);
	if (parse_positive_int(argv[3], &sim->time_to_eat_ms))
		return (print_usage_and_exit(), 1);
	if (parse_positive_int(argv[4], &sim->time_to_sleep_ms))
		return (print_usage_and_exit(), 1);
	sim->required_meals = 0;
	if (argc == 6 && parse_positive_int(argv[5], &sim->required_meals))
		return (print_usage_and_exit(), 1);
	return (0);
}
