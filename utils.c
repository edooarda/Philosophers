/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 13:00:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 17:59:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int long	time_stamp(t_data *data)
{
	long int	current_time;
	long int	new_time;

	current_time = get_current_time();
	new_time = current_time - data->start_time;
	return (new_time);
}

void	print_message(t_philo *philo, int flag)
{
	int long	time;

	pthread_mutex_lock(philo->print_lock);
	time = time_stamp(philo->data);
	if (flag == EAT)
		printf(GREEN"%ld %d is eating\n"RESET, time, philo->philo_id);
	if (flag == SLEEPY)
		printf(CYAN"%ld %d is sleeping\n"RESET, time, philo->philo_id);
	if (flag == HASHI)
		printf(CYAN"%ld %d has taken a fork\n"RESET, time, philo->philo_id);
	if (flag == THINK)
		printf(PINK"%ld %d is thinking\n"RESET, time, philo->philo_id);
	if (flag == DIED)
		printf(RED"%ld %d has died\n"RESET, time, philo->philo_id);
	if (flag == FULL)
		printf(YEL"ALL philos received enough food\n"RESET);
	pthread_mutex_unlock(philo->print_lock);
}

int long	get_current_time(void)
{
	struct timeval	time;
	int long		time_milisec;

	if (gettimeofday(&time, NULL) != 0)
	{
		write(2, "Problem Setting Time",21);
		return (0);
	}
	time_milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_milisec);
}

void	resting(int long must_wait)
{
	int long	current_time;
	current_time = get_current_time();
	while ((get_current_time() - current_time) < must_wait)
	{
		usleep(100);
	}
}
