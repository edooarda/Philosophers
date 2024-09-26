/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:12:09 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/26 16:25:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting_philo(t_data *data)
{
	int	i;

	i = 0;
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

static void	creating_philo_thread(t_data *data)
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

void	init_table(t_data *data)
{
	int	i;

	i = 0;
	data->table = malloc(data->nb_philos * sizeof(t_philo));
	if (data->table == NULL)
	{
		printf("Fail allocation memory\n");
		return ;
	}
	while (i < data->nb_philos)
	{
		data->table[i].philo_id = i + 1;
		data->table[i].nb_meals = 0;
		data->table[i].r_hashi = &data->cutlery[i];
		data->table[i].l_hashi = &data->cutlery[(i + 1) % data->nb_philos];
		data->table[i].last_meal = 0;
		data->table[i].is_alive = true;
		data->table[i].data = data;
		i++;
	}
	creating_philo_thread(data);
	// waiting_philo(data);
}
