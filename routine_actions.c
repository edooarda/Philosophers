/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:55:45 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/13 22:28:26 by edooarda      ########   odam.nl         */
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
		return (true);
	}
	return (false);
}

static bool	pickup_second_hashi(t_philo *philo, pthread_mutex_t *second_hashi)
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
		return (true);
	}
	else
	{
		write(2, "Error locking Hashi\n", 21);
		return (false);
	}
}

static bool	pickup_first_hashi(t_philo *philo,
	pthread_mutex_t *frst_hashi, pthread_mutex_t *scnd_hashi)
{
	if (pthread_mutex_lock(frst_hashi) == 0)
	{
		print_message(philo, HASHI);
		if (is_single_philo(philo) == true)
			return (false);
		pickup_second_hashi(philo, scnd_hashi);
		pthread_mutex_unlock(frst_hashi);
		return (true);
	}
	else
	{
		write(2, "Error locking Hashi\n", 20);
		return (false);
	}
}

bool	eating(t_philo *philo)
{
	pthread_mutex_t	*frst_hashi;
	pthread_mutex_t	*scnd_hashi;

	if (philo->philo_id % 2 == 0)
	{
		frst_hashi = philo->l_hashi;
		scnd_hashi = philo->r_hashi;
	}
	else
	{
		frst_hashi = philo->r_hashi;
		scnd_hashi = philo->l_hashi;
	}
	if (pickup_first_hashi(philo, frst_hashi, scnd_hashi) == false)
		return (false);
	return (true);
}

void	sleeping_and_thinking(t_philo *philo)
{
	int long	time_to_think;

	time_to_think = 2 * philo->table->time_to_eat - philo->table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	print_message(philo, SLEEPY);
	resting(philo->table->time_to_sleep, philo);
	print_message(philo, THINK);
	if (philo->table->nb_philos % 2 != 0)
		resting(time_to_think, philo);
}
