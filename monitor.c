/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/25 17:29:48 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// checker for dead and for a full belly
bool	is_belly_full(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->shared_lock);
	if (philo->data->has_meals_counter == true)
	{
		if (philo->nb_meals == philo->data->how_many_meals)
		{
			return (true);
			// philo->data->full_belly++;
		}
	}
	// if (philo->data->full_belly == philo->data->nb_philos)
	// {
	// 	// pthread_mutex_unlock(&philo->data->shared_lock);
	// 	return (true);
	// }
	// pthread_mutex_unlock(&philo->data->shared_lock);
	return (false);
}

bool	is_starved(t_philo *philo)
{
	
}