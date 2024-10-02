/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:55:45 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/02 14:09:12 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_single_philo(t_philo *philo)
{
	if (philo->table->nb_philos == 1)
	{
		pthread_mutex_lock(&philo->table->meal_lock);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&philo->table->meal_lock);
		pthread_mutex_unlock(philo->r_hashi);
		resting(philo->table->time_to_die, philo);
		pthread_mutex_destroy(philo->r_hashi);
		return (true);
	}
	return (false);
}

static void	pickup_second_hashi(t_philo *philo, pthread_mutex_t *second_hashi)
{
	if (pthread_mutex_lock(second_hashi) == 0)
	{
		print_message(philo, HASHI);
		print_message(philo, EAT);
		pthread_mutex_lock(&philo->table->meal_lock);
		philo->last_meal = get_current_time();
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->table->meal_lock);
		resting(philo->table->time_to_eat, philo);
		pthread_mutex_unlock(second_hashi);
	}
	else
		write(2, "Error locking Hashi\n", 22);
}

static bool	eating_even(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_hashi) == 0)
	{
		print_message(philo, HASHI);
		pickup_second_hashi(philo, philo->l_hashi);
		pthread_mutex_unlock(philo->r_hashi);
	}
	else
	{
		write(2, "Error locking Hashi\n", 22);
		return (false);
	}
	return (true);
}

static bool	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_hashi) == 0)
	{
		print_message(philo, HASHI);
		if (is_single_philo(philo) == true)
			return (false);
		pickup_second_hashi(philo, philo->l_hashi);
		pthread_mutex_unlock(philo->r_hashi);
	}
	else
	{
		write(2, "Error locking Hashi\n", 22);
		return (false);
	}
	return (true);
}

static void	sleeping_and_thinking(t_philo *philo)
{
	print_message(philo, SLEEPY);
	resting(philo->table->time_to_sleep, philo);
	print_message(philo, THINK);
}
// bool	simulation_stopper(t_philo *philo)
// {
	
// }

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
			if (eating(philo) == false)
				return (NULL);
		}
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->is_alive == false
			|| philo->nb_meals == philo->table->how_many_meals)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
		sleeping_and_thinking(philo);
	}
	return (NULL);
}
