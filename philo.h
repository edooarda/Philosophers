/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:24 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/23 23:00:40 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYAN "\033[36m"
# define PINK "\033[35m"
# define YEL "\033[0;33m"
# define RESET "\033[0m"

typedef struct s_data_philo
{
	int long	start_time;
	int			nb_philos;
	int			limit_time_to_die;
	int			limit_time_to_eat;
	int			limit_time_to_sleep;
	bool		has_meals_counter;
	int			how_many_meals;
}	t_data;


bool	input_checker(int argc, char **argv);
long	ft_atol(const char *str);
int long	get_current_time(void);

#endif
