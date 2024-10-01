/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   supervisor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/01 16:00:30 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	had_enough_meals(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	if (table->has_meals_counter == true)
	{
		while (i < table->nb_philos)
		{
			if (table->philo[i].nb_meals == table->how_many_meals)
			{
				table->full_belly++;
				pthread_mutex_unlock(&table->meal_lock);
				return (true);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (false);
}

bool	is_someone_dead(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->dead_lock);
	pthread_mutex_lock(&table->meal_lock);
	while (i < table->nb_philos)
	{
		if (table->philo[i].last_meal != 0 && get_current_time() - table->philo[i].last_meal > table->limit_time_to_die)
		{
			table->is_alive = false;
			printf(RED"%ld %d has died\n"RESET, get_current_time() - table->start_time, table->philo[i].philo_id);
			pthread_mutex_unlock(&table->meal_lock);
			pthread_mutex_unlock(&table->dead_lock);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	pthread_mutex_unlock(&table->dead_lock);
	return (false);
}

void *observe(t_table *table)
{
	while (1)
	{
		if (is_someone_dead(table) == true || had_enough_meals(table) == true)
		{
			return (NULL);
		}
	}
	return (NULL);
}
