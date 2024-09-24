/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 16:57:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/24 17:22:21 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.start_time = get_current_time();
	data.nb_philos = ft_atol(argv[1]);
	data.limit_time_to_die = ft_atol(argv[2]);
	data.limit_time_to_eat = ft_atol(argv[3]);
	data.limit_time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		data.has_meals_counter = true;
		data.how_many_meals = ft_atol(argv[5]);
	}
	else
	{
		data.has_meals_counter = false;
		data.how_many_meals = -1;
	}
	// if (pthread_mutex_init(&data.print, NULL) != 0)
	// {
	// 	write(2, "Error Init mutex Print\n", 24);
	// 	// return ;
	// }
	return (data);
}
