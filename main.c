/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/23 23:55:51 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_data *data)
{
	int long	start_time;
	int long	must_wait;

	start_time = data->start_time;
	must_wait = data->limit_time_to_eat;
	printf(GREEN"%ld %d is eating\n"RESET, start_time, data->nb_philos);
	while((get_current_time() - start_time) < must_wait)
	{
		usleep(100);
	}
	// return (NULL);
}

void	thinking(t_data *data)
{
	int long	start_time;

	start_time = get_current_time();
	printf(PINK"%ld %d is thinking\n"RESET, start_time, data->nb_philos);
}

void	sleeping(t_data *data)
{
	int	i;
	int long	start_time;
	int long	must_wait;

	i = 0;
	start_time = data->start_time;
	must_wait = data->limit_time_to_sleep;
	printf(CYAN"%ld %d is sleeping\n"RESET, start_time, i);
	while((get_current_time() - start_time) < must_wait)
	{
		usleep(100);
	}
	// return (NULL);
}

// void	ft_dead()
// {
// 	printf(RED"timestamp X has died\n"RESET);
// }

int long	get_current_time(void)
{
	struct timeval	time;
	int long		time_milisec;

	if (gettimeofday(&time, NULL) != 0)
		return (printf("Problem Setting Time"), 0);
	time_milisec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_milisec);
}
void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data*)arg;
	eating(data);
	sleeping(data);
	thinking(data);
	return (NULL);
}

t_data	init_struct(int argc, char **argv)
{
	t_data	data;

	data.start_time = get_current_time();
	data.nb_philos = ft_atol(argv[1]);
	data.limit_time_to_die = ft_atol(argv[2]);
	data.limit_time_to_eat = ft_atol(argv[3]);
	data.limit_time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		data.has_meals_counter = true;
		data.how_many_meals = ft_atol(argv[5]);
	}
	else
	{
		data.has_meals_counter = false;
		data.how_many_meals = -1;
	}
	return (data);
}

int	main(int argc, char **argv)
{
	pthread_t	philo, philo2;
	t_data		data;
	pthread_mutex_t	l_hashi;
	pthread_mutex_t	r_hashi;

	pthread_mutex_init(&l_hashi, NULL);
	pthread_mutex_init(&r_hashi, NULL);
	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🥢 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (false);
	}
	data = init_struct(argc, argv);
	pthread_create(&philo, NULL, &routine, &data);
	pthread_create(&philo2, NULL, &routine, &data);
	pthread_join(philo, NULL);
	pthread_join(philo2, NULL);
	pthread_mutex_destroy(&l_hashi);
	pthread_mutex_destroy(&r_hashi);
	return (0);
}
