/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 17:45:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/01 17:44:44 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creating_philo_thread(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].table_id, NULL,
				&routine, &table->philo[i]) != 0)
		{
			pthread_mutex_unlock(&table->start_lock);
			write(2, "ERROR creating Philo thread\n", 29);
			return (i);
		}
		i++;
	}
	table->start_time = get_current_time();
	pthread_mutex_unlock(&table->start_lock);
	return (i);
}

void	waiting_threads(t_table *table, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (pthread_join(table->philo[i].table_id, NULL) != 0)
		{
			write(2, "ERROR join Philo thread\n", 22);
			return ;
		}
		i++;
	}
}
