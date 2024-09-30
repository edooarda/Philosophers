/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 15:12:13 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	adding_cutlery(t_table *table)
{
	int	i;

	i = 0;
	table->cutlery = malloc(table->nb_philos * sizeof(pthread_mutex_t));
	if (table->cutlery == NULL)
	{
		write(2, "Error allocation memory for Cutlery\n", 37);
		return ;
	}
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->cutlery[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&table->cutlery[i]);
				free(&table->cutlery[i]);
				write(2, "ERROR creating mutex, detroing previous\n", 41);
				i--;
			}
			// free memory for forks outside the loop?
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	watcher;

	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🥢 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (false);
	}
	table = init_table(argc, argv);
	adding_cutlery(&table);
	init_philo(&table);
	supervisor(&table, &watcher);
	creating_philo_thread(&table);
	waiting_threads(&table, watcher);
	if (table.has_meals_counter == true)
	{
		printf("nb of philos: %d and full belly %d\n\n", table.nb_philos, table.full_belly);
		if (table.full_belly >= table.nb_philos)
			print_message(table.philo, FULL);
	}
	return (0);
}

// TODO free memory from mutex array and from philo array
// destroy print mutex, meals_counter_mutex and array the mutexes