/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/03 11:39:11 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	adding_cutlery(t_table *table)
{
	int	i;

	i = 0;
	table->cutlery = malloc(table->nb_philos * sizeof(pthread_mutex_t));
	if (table->cutlery == NULL)
	{
		write(2, "Error allocation memory for Cutlery\n", 37);
		return (false);
	}
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->cutlery[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&table->cutlery[i]);
				write(2, "ERROR creating mutex, detroing previous\n", 41);
				i--;
			}
			free(table->cutlery);
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🥢 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (1);
	}
	table = init_table(argc, argv);
	if (adding_cutlery(&table) == false)
		return (1);
	if (init_philo(&table) == false)
	{
		free(table.cutlery);
		return (1);
	}
	i = creating_philo_thread(&table);
	supervisor(&table);
	waiting_threads(&table, i);
	cleaner(&table);
	return (0);
}
