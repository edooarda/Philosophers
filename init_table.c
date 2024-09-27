/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:12:09 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 17:46:23 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		data->table[i].is_alive = true;
		data->table[i].philo_id = i + 1;
		data->table[i].nb_meals = 0;
		data->table[i].last_meal = get_current_time();
		data->table[i].l_hashi = &data->cutlery[(i + 1) % data->nb_philos];
		data->table[i].r_hashi = &data->cutlery[i];
		data->table[i].print_lock = &data->print_lock;
		data->table[i].dead_lock = &data->dead_lock;
		data->table[i].meal_lock = &data->meal_lock;
		data->table[i].data = data;
		i++;
	}
}
