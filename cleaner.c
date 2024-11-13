/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 16:52:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/13 22:27:21 by edooarda      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_destroier(t_table *table)
{
	int	i;

	i = 0;
	if (table->cutlery != NULL)
	{
		while (i < table->nb_philos)
		{
			pthread_mutex_destroy(&table->cutlery[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->start_lock);
}

void	cleaner(t_table *table)
{
	mutexes_destroier(table);
	if (table->cutlery != NULL)
	{
		free(table->cutlery);
	}
	if (table->philo != NULL)
	{
		free(table->philo);
	}
}
