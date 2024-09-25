/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/25 13:41:51 by edribeir      ########   odam.nl         */
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
		// if (data->table[i].philo_id == data->nb_philos)
		// {
		// 	data->table[i].l_hashi = data->table[i].r_hashi;
		// 	data->table[i].r_hashi = &data->cutlery[i];
		// }
		data->table[i].last_meal = 0;
		data->table[i].data = data;
		i++;
	}
	creating_philo_thread(data);
	waiting_philo(data);
}

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
		printf("passei aqui criando hashis\n");
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
	t_data	data;

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
	return (0);
}
