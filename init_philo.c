/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:12:09 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/03 10:43:31 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(table->nb_philos * sizeof(t_philo));
	if (table->philo == NULL)
	{
		printf("Fail allocation memory\n");
		return (false);
	}
	while (i < table->nb_philos)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].nb_meals = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].r_hashi = &table->cutlery[i];
		if (table->philo[i].philo_id == table->nb_philos)
			table->philo[i].l_hashi = &table->cutlery[0];
		else
			table->philo[i].l_hashi = &table->cutlery[i + 1];
		table->philo[i].table = table;
		i++;
	}
	return (true);
}
