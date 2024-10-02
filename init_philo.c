/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:12:09 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/02 10:45:39 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(table->nb_philos * sizeof(t_philo));
	if (table->philo == NULL)
	{
		printf("Fail allocation memory\n");
		return ;
	}
	while (i < table->nb_philos)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].nb_meals = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].l_hashi = &table->cutlery[(i + 1) % table->nb_philos];
		table->philo[i].r_hashi = &table->cutlery[i];
		table->philo[i].table = table;
		i++;
	}
}
