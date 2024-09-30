/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   supervisor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 16:07:31 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_starved(t_philo *philo)
// {
// 	long int	last_meal;
// 	long int	current_time;

// 	current_time = get_current_time();
// 	usleep(100);
// 	pthread_mutex_lock(philo->meal_lock);
// 	last_meal = philo->last_meal;
// 	pthread_mutex_unlock(philo->meal_lock);
// 	if (current_time - last_meal > philo->data->limit_time_to_die)
// 	{
// 		pthread_mutex_lock(philo->dead_lock);
// 		philo->data->is_alive = false;
// 		pthread_mutex_unlock(philo->dead_lock);
// 		print_message(philo, DIED);
// 		return (true);
// 	}
// 	return (false);
// }
// {
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (philo->is_alive == false)
// 	{
// 		printf("is alive -> %d\n", philo->philo_id);
// 		pthread_mutex_unlock(philo->dead_lock);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(philo->dead_lock);
// 	return (false);
// }

bool	had_enough_meals(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	if (table->has_meals_counter == true)
	{
		while (i < table->nb_philos)
		{
			if (table->philo[i].nb_meals == table->how_many_meals)
			{
				table->full_belly++;
				pthread_mutex_unlock(&table->meal_lock);
				return (true);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (false);
}

bool	is_someone_dead(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->dead_lock);
	i = 0;
	while (i < table->nb_philos)
	{
		if (get_current_time() - table->philo[i].last_meal > table->limit_time_to_die)
		{
			table->is_alive = false;
			print_message(&table->philo[i], DIED);
			pthread_mutex_unlock(&table->dead_lock);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&table->dead_lock);
	return (false);
}

void *observe(void *arg)
{
	// int	i;
	t_table *table;

	table = (t_table *)arg;
	while (1)
	{
		if (is_someone_dead(table) == true || had_enough_meals(table) == true)
		{
			// usleep(100);
			// break ;
			return (NULL);
		}
		// if (had_enough_meals(table) == true)
		// {
		// 	// pthread_mutex_unlock(&table->meal_lock);
		// 	// pthread_mutex_lock(&table->print_lock);
		// 	// printf(YEL"All Philos are with a full belly\n"RESET);
		// 	usleep(100);
		// 	// pthread_mutex_unlock(&table->print_lock);
		// 	break ;
		// }
		// i = 0;
		// while (i < table->nb_philos)
		// {
		// 	if (is_starved(&table->philo[i]) == true)
		// 		return (NULL) ;
		// 	i++;
		// }
		// usleep(100);
	}
	return (NULL);
}

void	supervisor(t_table *table, pthread_t *watcher)
{
	pthread_create(watcher, NULL, &observe, table);
	// fazer checkagem da criacao do supervisor
}
