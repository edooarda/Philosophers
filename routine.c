/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/02 14:15:10 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/02 17:54:11 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_to_stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
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
	if ((philo->philo_id % 2) == 0)
	{
		print_message(philo, THINK);
		resting(philo->table->time_to_eat / 2, philo);
	}
	while (1)
	{
		if (eating(philo) == false)
		{
			return (NULL);
		}
		if (is_to_stop_simulation(philo) == true)
			return (NULL);
		sleeping_and_thinking(philo);
	}
	return (NULL);
}
