/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 17:51:00 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	adding_cutlery(t_data *data)
{
	int	i;

	i = 0;
	data->cutlery = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (data->cutlery == NULL)
	{
		write(2, "Error allocation memory for Cutlery\n", 37);
		return ;
	}
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->cutlery[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&data->cutlery[i]);
				free(&data->cutlery[i]);
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
	t_data		data;
	pthread_t	watcher;

	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🥢 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (false);
	}
	data = init_data(argc, argv);
	adding_cutlery(&data);
	init_table(&data);
	supervisor(&data, &watcher);
	creating_philo_thread(&data);
	waiting_threads(&data, watcher);
	// pthread_mutex_lock(&data.print_lock);
	if (data.has_meals_counter == true)
	{
		printf("nb of philos: %d and full belly %d\n\n", data.nb_philos, data.full_belly);
		if (data.full_belly >= data.nb_philos)
			print_message(data.table, FULL);
	}
	// pthread_mutex_unlock(&data.print_lock);
	return (0);
}

// TODO free memory from mutex array and from philo array
// destroy print mutex, meals_counter_mutex and array the mutexes