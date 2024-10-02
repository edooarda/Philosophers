/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:55:45 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/02 14:18:43 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_single_philo(t_philo *philo)
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

void	pickup_second_hashi(t_philo *philo, pthread_mutex_t *second_hashi)
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

bool	eating_even(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_hashi) == 0)
	{
		print_message(philo, HASHI);
		pickup_second_hashi(philo, philo->r_hashi);
		pthread_mutex_unlock(philo->l_hashi);
	}
	else
	{
		write(2, "Error locking Hashi\n", 22);
		return (false);
	}
	return (true);
}

bool	eating_odd(t_philo *philo)
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

void	sleeping_and_thinking(t_philo *philo)
{
	print_message(philo, SLEEPY);
	resting(philo->table->time_to_sleep, philo);
	print_message(philo, THINK);
}
