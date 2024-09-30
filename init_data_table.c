/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_table.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:57:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 16:05:56 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	init_table(int argc, char **argv)
{
	t_table	table;

	table.start_time = 0;
	table.is_alive = true;
	table.nb_philos = ft_atol(argv[1]);
	table.limit_time_to_die = ft_atol(argv[2]);
	table.limit_time_to_eat = ft_atol(argv[3]);
	table.limit_time_to_sleep = ft_atol(argv[4]);
	table.full_belly = 0;
	if (argc == 6)
	{
		table.has_meals_counter = true;
		table.how_many_meals = ft_atol(argv[5]);
	}
	else
	{
		table.has_meals_counter = false;
		table.how_many_meals = -1;
	}
	if (pthread_mutex_init(&table.print_lock, NULL) != 0)
	{
		write(2, "Error Init mutex Print\n", 24);
		// return ;
	}
	if (pthread_mutex_init(&table.meal_lock, NULL) != 0)
	{
		write(2, "Error Init mutex Meal Counter\n", 31);
		// return ;
	}
	if (pthread_mutex_init(&table.dead_lock, NULL) != 0)
	{
		write(2, "Error Init mutex Dead\n", 23);
		// return ;
	}
		if (pthread_mutex_init(&table.start_lock, NULL) != 0)
	{
		write(2, "Error Init mutex Start\n", 23);
		// return ;
	}
	table.philo = NULL;
	return (table);
}
