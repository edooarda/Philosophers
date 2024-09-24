/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:55:45 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/24 17:26:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_hashi);
	print_message(philo, HASHI);
	if (philo->data->nb_philos == 1)
	{
		resting(philo, philo->data->limit_time_to_die);
		dead(philo);
		return (false);
	}
	// printf("limit time to eat: %d\n", philo->data->limit_time_to_eat);
	pthread_mutex_lock(philo->r_hashi);
	print_message(philo, HASHI_R);
	print_message(philo, EAT);
	resting(philo, philo->data->limit_time_to_eat);
	pthread_mutex_unlock(philo->l_hashi);
	pthread_mutex_unlock(philo->r_hashi);
	return (true);
}

static void	thinking(t_philo *philo)
{
	printf(PINK"%ld %d is thinking\n"RESET,
		time_stamp(philo->data), philo->philo_id);
}

static void	sleeping(t_philo *philo)
{
	print_message(philo, SLEEPY);
	resting(philo, philo->data->limit_time_to_sleep);
}

void	dead(t_philo *philo)
{
	printf(RED"%ld %d has died\n"RESET,
		time_stamp(philo->data), philo->philo_id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (eating(philo) == false)
		return (NULL);
	sleeping(philo);
	thinking(philo);
	return (NULL);
}
