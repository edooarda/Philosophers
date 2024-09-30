/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 17:45:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 15:38:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creating_philo_thread(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philo[i].table_id, NULL,
				&routine, &table->philo[i]) != 0)
		{
			// free memory cutlery and philo
			pthread_mutex_unlock(&table->start_lock);
			write(2, "ERROR creating Philo thread\n", 22);
			return ;
		}
		i++;
	}
	table->start_time = get_current_time();
	pthread_mutex_unlock(&table->start_lock);
}

void	waiting_threads(t_table *table, pthread_t watcher)
{
	int	i;

	i = 0;
	if (pthread_join(watcher, NULL) != 0)
	{
		// free memory cutlery and philo_philo
		write(2, "ERROR join Supervisor thread\n", 22);
		return ;
	}
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philo[i].table_id, NULL) != 0)
		{
			// free memory cutlery and philo_table
			write(2, "ERROR join Philo thread\n", 22);
			return ;
		}
		i++;
	}
}
