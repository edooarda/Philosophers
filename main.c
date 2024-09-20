/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/20 16:40:13 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*ft_eating(void *)
// {
// 	printf(GREEN"timestamp X is eating\n"RESET);
// 	return (NULL);
// }

// void	*ft_thinking(void*)
// {
// 	int	i;

// 	i = 0;
// 	while(i < 5)
// 	{
// 		sleep(2);
// 		printf(PINK"timestamp %d is thinking\n"RESET, i);
// 		i++;
// 	}
// 	return (NULL);
// }

// void	*ft_sleeping(void*)
// {
// 	int	i;

// 	i = 0;
// 	while(i < 8)
// 	{
// 		sleep(1);
// 		printf(CYAN"timestamp %d is sleeping\n"RESET, i);
// 		i++;
// 	}
// 	return (NULL);
// }

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

void	init_struct(int argc, char **argv)
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
}

int	main(int argc, char **argv)
{
	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🥢 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (false);
	}
	init_struct(argc, argv);
	return (0);
}
