/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:55:45 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 16:04:43 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_single_philo(t_philo *philo)
{
	if (philo->table->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->r_hashi);
		resting(philo->table->limit_time_to_die);
		pthread_mutex_destroy(philo->r_hashi);
		return (true);
	}
	return (false);
}

void	pickup_second_hashi(t_philo *philo, pthread_mutex_t *second_hashi)
{
	if (pthread_mutex_lock(second_hashi) == 0)
	{
		if (philo->table->is_alive == true)
			print_message(philo, HASHI);
		if (philo->table->is_alive == true)
			print_message(philo, EAT);
		pthread_mutex_lock(&philo->table->meal_lock);
		philo->last_meal = get_current_time();
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->table->meal_lock);
		resting(philo->table->limit_time_to_eat);
		pthread_mutex_unlock(second_hashi);
	}
	else
		write(2, "Error locking Hashi\n",22);
}

static bool eating(t_philo *philo)
{
	pthread_mutex_t *first_hashi;
	pthread_mutex_t *second_hashi;

	first_hashi = philo->l_hashi;
	second_hashi = philo->r_hashi;
	if (philo->r_hashi < philo->l_hashi)
	{
		first_hashi = philo->r_hashi;
		second_hashi = philo->l_hashi;
	}
	if (pthread_mutex_lock(first_hashi) == 0)
	{
		if (philo->table->is_alive == true)
			print_message(philo, HASHI);
		if(is_single_philo(philo) == true)
			return (false);
		// if (philo->table->is_alive == false)
		// 	return (false);
		pickup_second_hashi(philo, second_hashi);
		pthread_mutex_unlock(first_hashi);
	}
	else
	{
		write(2, "Error locking Hashi\n",22);
		return (false);
	}
	return (true);
}

static void	sleeping(t_philo *philo)
{
	if (philo->table->is_alive == true)
		print_message(philo, SLEEPY);
	resting(philo->table->limit_time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->start_lock);
	pthread_mutex_unlock(&philo->table->start_lock);
	if ((philo->philo_id % 2) == 0)
		resting(philo->table->limit_time_to_eat / 2);
	while (1)
	{
		// pthread_mutex_lock(&philo->table->alive_lock);
		// if (philo->table->is_alive == false)
		// {
		// 	pthread_mutex_unlock(&philo->table->alive_lock);
		// 	return (NULL);
		// }
		// pthread_mutex_unlock(&philo->table->alive_lock);
		if (eating(philo) == false)
			return (NULL);
		sleeping(philo);
		if (had_enough_meals(philo->table) == true)
			return (NULL);
		if (is_someone_dead(philo->table) == true)
		{
			printf("to morrendo por dentro\n");
			return (NULL);
		}
		if (philo->table->is_alive == true)
			print_message(philo, THINK);
	}
	return (NULL);
}
