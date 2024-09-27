/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 17:45:49 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 17:47:10 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creating_philo_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->table[i].table_id, NULL,
				&routine, &data->table[i]) != 0)
		{
			// free memory cutlery and philo_table
			write(2, "ERROR creating Philo thread\n", 22);
			return ;
		}
		i++;
	}
}

void	waiting_threads(t_data *data, pthread_t watcher)
{
	int	i;

	i = 0;
	if (pthread_join(watcher, NULL) != 0)
	{
		// free memory cutlery and philo_table
		write(2, "ERROR join Supervisor thread\n", 22);
		return ;
	}
	while (i < data->nb_philos)
	{
		if (pthread_join(data->table[i].table_id, NULL) != 0)
		{
			// free memory cutlery and philo_table
			write(2, "ERROR join Philo thread\n", 22);
			return ;
		}
		i++;
	}
}
