/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 18:35:20 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	is_starved(t_philo *philo)
{
	long int	last_meal;
	long int	current_time;

	current_time = get_current_time();
	usleep(100);
	pthread_mutex_lock(philo->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	if (current_time - last_meal > philo->data->limit_time_to_die)
	{
		philo->is_alive = false;
		print_message(philo, DIED);
		return (true);
	}
	return (false);
}
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

bool	had_enough_meals(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meal_lock);
	if (data->has_meals_counter == true)
	{
		while (i < data->nb_philos)
		{
			if (data->table[i].nb_meals == data->how_many_meals)
			{
				// printf("valido?\n");
				data->full_belly++;
				pthread_mutex_unlock(&data->meal_lock);
				return (true);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (false);
}

bool	is_someone_dead(t_data *data)
{
	int long	last_meal;
	int			i;

	// pthread_mutex_lock(philo->dead_lock);
	// // meal = philo->last_meal;
	i = 0;
	// time = get_current_time() - philo->last_meal;
	// if (time > philo->data->limit_time_to_die && philo->nb_meals != philo->data->how_many_meals)
	// {
	// 	pthread_mutex_lock(&philo->data->private_lock);
	// 	philo->is_alive = false;
	// 	pthread_mutex_unlock(&philo->data->private_lock);
	// 	print_message(philo, DIED);
	// 	resting(philo, philo->data->limit_time_to_die);
	// 	// dead(philo);
	// 	// printf("MORRI!\n");
	// 	pthread_mutex_unlock(&philo->data->shared_lock);
	// 	return (true);
	// }
	// pthread_mutex_unlock(&philo->data->shared_lock);
	// return (false);
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		last_meal = data->table[i].last_meal;
		pthread_mutex_unlock(&data->meal_lock);
		if (get_current_time() - last_meal > data->limit_time_to_die)
		{
			printf("DEADDDD!!!!!!!!!\n");
			pthread_mutex_lock(&data->dead_lock);
			data->table[i].is_alive = false;
			print_message(&data->table[i], DIED);
			pthread_mutex_unlock(&data->dead_lock);
			resting(data->limit_time_to_die);
			return (true);
		}
		i++;
	}
	return (false);
}
void *observe(void *arg)
{
	int	i;
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_someone_dead(data) == true)
		{
			break ;
		}
		if (had_enough_meals(data) == true)
		{
			// pthread_mutex_unlock(&data->meal_lock);
			// pthread_mutex_lock(&data->print_lock);
			// printf(YEL"All Philos are with a full belly\n"RESET);
			usleep(100);
			// pthread_mutex_unlock(&data->print_lock);
			break ;
		}
		i = 0;
		while (i < data->nb_philos)
		{
			if (is_starved(&data->table[i]) == true)
				return (NULL) ;
			i++;
		}
		// usleep(100);
	}
	return (NULL);
}

void	supervisor(t_data *data, pthread_t *watcher)
{
	pthread_create(watcher, NULL, &observe, data);
	// fazer checkagem da criacao do supervisor
}



// {
// 	int	i;

// 	i = 0;
// 	while (1)
// 	{
// 		i = 0;
// 	if (data->has_meals_counter == true)
// 	{
// 		printf("essa eh a quantidade de barrigas cheias %d\n", data->full_belly);
// 		if (data->full_belly == data->nb_philos)
// 		{
// 			print_message(&data->table[i], FULL);
// 			return ;
// 		}
// 	}
// 		while (i < data->nb_philos)
// 		{
// 			if (is_starved(&data->table[i]) == false)
// 			{
// 				// print_message(&data->table[i], DIED);
// 				return ;
// 			}
// 			if (data->full_belly == data->nb_philos)
// 			{
// 				print_message(&data->table[i], FULL);
// 				return ;
// 			}
// 			// resting(&data->table[i], data->limit_time_to_die);
// 			i++;
// 		}
// 		usleep(1000);
// 	}
// 	// pthread_mutex_lock(&philo->data->shared_lock);
// 	// if (philo->is_alive == false || philo->data->full_belly == philo->data->nb_philos)
// 	// {
// 	// 	pthread_mutex_unlock(&philo->data->shared_lock);
// 	// 	if (philo->data->has_meals_counter == true)
// 	// 	{
// 	// 		if (philo->data->how_many_meals == philo->data->full_belly)
// 	// 			print_message(philo, FULL);
// 	// 	}
// 	// 	return (true);
// 	// }
// 	// pthread_mutex_unlock(&philo->data->shared_lock);
// 	// return (false);
// }