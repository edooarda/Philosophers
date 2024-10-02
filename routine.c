/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/02 14:15:10 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/02 14:23:03 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	simulation_stopper(t_philo *philo)
{
	if (philo->table->is_alive == false
		|| philo->nb_meals == philo->table->how_many_meals)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->start_lock);
	pthread_mutex_unlock(&philo->table->start_lock);
	while (1)
	{
		if ((philo->philo_id % 2) == 0)
		{
			resting(philo->table->time_to_eat / 2, philo);
			if (eating_even(philo) == false)
				return (NULL);
		}
		else
		{
			if (eating_odd(philo) == false)
				return (NULL);
		}
		pthread_mutex_lock(&philo->table->dead_lock);
		if (simulation_stopper(philo) == true)
			return (NULL);
		sleeping_and_thinking(philo);
	}
	return (NULL);
}
