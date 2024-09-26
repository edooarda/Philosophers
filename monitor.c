/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/26 17:34:29 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// checker for dead and for a full belly
bool	is_someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->private_lock);
	if (philo->is_alive == false)
	{
		printf("is alive -> %d\n", philo->philo_id);
		pthread_mutex_unlock(&philo->data->private_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->private_lock);
	return (false);
}

bool	had_enough_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->shared_lock);
	if (philo->data->has_meals_counter == true)
	{
		if (philo->nb_meals == philo->data->how_many_meals)
		{
			printf("valido?\n");
			philo->data->full_belly++;
			pthread_mutex_unlock(&philo->data->shared_lock);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->data->shared_lock);
	return (false);
}

bool	is_starved(t_philo *philo)
{
	// int long	meal;
	int long	time;

	pthread_mutex_lock(&philo->data->shared_lock);
	// meal = philo->last_meal;
	time = get_current_time() - philo->last_meal;
	if (time > philo->data->limit_time_to_die && philo->nb_meals != philo->data->how_many_meals)
	{
		pthread_mutex_lock(&philo->data->private_lock);
		philo->is_alive = false;
		pthread_mutex_unlock(&philo->data->private_lock);
		print_message(philo, DIED);
		resting(philo, philo->data->limit_time_to_die);
		// dead(philo);
		// printf("MORRI!\n");
		pthread_mutex_unlock(&philo->data->shared_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->shared_lock);
	return (false);
}

void	monitor(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
	if (data->has_meals_counter == true)
	{
		printf("essa eh a quantidade de barrigas cheias %d\n", data->full_belly);
		if (data->full_belly == data->nb_philos)
		{
			print_message(&data->table[i], FULL);
			return ;
		}
	}
		while (i < data->nb_philos)
		{
			if (is_starved(&data->table[i]) == false)
			{
				// print_message(&data->table[i], DIED);
				return ;
			}
			if (data->full_belly == data->nb_philos)
			{
				print_message(&data->table[i], FULL);
				return ;
			}
			// resting(&data->table[i], data->limit_time_to_die);
			i++;
		}
		usleep(1000);
	}
	// pthread_mutex_lock(&philo->data->shared_lock);
	// if (philo->is_alive == false || philo->data->full_belly == philo->data->nb_philos)
	// {
	// 	pthread_mutex_unlock(&philo->data->shared_lock);
	// 	if (philo->data->has_meals_counter == true)
	// 	{
	// 		if (philo->data->how_many_meals == philo->data->full_belly)
	// 			print_message(philo, FULL);
	// 	}
	// 	return (true);
	// }
	// pthread_mutex_unlock(&philo->data->shared_lock);
	// return (false);
}