/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   supervisor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/01 17:39:25 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	had_enough_meals(t_table *table)
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
				pthread_mutex_unlock(&table->meal_lock);
				return (true);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (false);
}

static bool	is_someone_dead(t_table *tb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&tb->dead_lock);
	pthread_mutex_lock(&tb->meal_lock);
	while (i < tb->nb_philos)
	{
		if (tb->philo[i].last_meal != 0
			&& get_current_time() - tb->philo[i].last_meal > tb->time_to_die)
		{
			tb->is_alive = false;
			printf(RED"%ld %d has died\n"RESET,
				get_current_time() - tb->start_time, tb->philo[i].philo_id);
			pthread_mutex_unlock(&tb->meal_lock);
			pthread_mutex_unlock(&tb->dead_lock);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&tb->meal_lock);
	pthread_mutex_unlock(&tb->dead_lock);
	return (false);
}

void	*observe(t_table *table)
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
