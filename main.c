/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/11 18:34:10 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_eating(void *)
{
	printf(GREEN"timestamp X is eating\n"RESET);
	return (NULL);
}

void	*ft_thinking(void*)
{
	int	i;

	i = 0;
	while(i < 5)
	{
		sleep(2);
		printf(PINK"timestamp %d is thinking\n"RESET, i);
		i++;
	}
	return (NULL);
}

void	*ft_sleeping(void*)
{
	int	i;

	i = 0;
	while(i < 8)
	{
		sleep(1);
		printf(CYAN"timestamp %d is sleeping\n"RESET, i);
		i++;
	}
	return (NULL);
}

void	ft_dead()
{
	printf(RED"timestamp X has died\n"RESET);
}


int	main(int argc, char **argv)
{
	pthread_t new_thread1;
	pthread_t new_thread2;
	pthread_t new_thread3;

	if (input_checker(argc, argv) == false)
	{
		printf(YEL"Correct Input\n"RESET);
		printf("\t 🔢 PHILOS ⌛ DIE ⌛ EAT ⌛ SLEEP (🍴 TIMES MUST EAT)\n");
		printf("\n\t./philo 5 410 100 100\t OR \t./philo 5 410 100 100 10\n\n");
		return (false);
	}
	pthread_create(&new_thread1, NULL, ft_sleeping, NULL);
	pthread_create(&new_thread2, NULL, ft_thinking, NULL);
	pthread_create(&new_thread3, NULL, ft_eating, NULL); // why the function without while goes first?
	pthread_join(new_thread1, NULL);
	pthread_join(new_thread2, NULL);
	pthread_join(new_thread3, NULL);
	return (0);
}
