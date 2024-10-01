/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_table.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:57:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/01 17:39:11 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		write(2, "Error Init mutex Meal Counter\n", 31);
		return (1);
	}
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->meal_lock);
		write(2, "Error Init mutex Dead\n", 23);
		return (1);
	}
	if (pthread_mutex_init(&table->start_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->dead_lock);
		write(2, "Error Init mutex Start\n", 24);
		return (1);
	}
	return (0);
}

t_table	init_table(int argc, char **argv)
{
	t_table	table;

	table.start_time = 0;
	table.is_alive = true;
	table.nb_philos = ft_atol(argv[1]);
	table.time_to_die = ft_atol(argv[2]);
	table.time_to_eat = ft_atol(argv[3]);
	table.time_to_sleep = ft_atol(argv[4]);
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
	init_mutexes(&table);
	table.philo = NULL;
	return (table);
}
