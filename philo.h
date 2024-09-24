/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:24 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/24 17:28:47 by edribeir      ########   odam.nl         */
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

# define EAT 1
# define SLEEPY 2
# define THINK 3
# define DIED 4
# define HASHI_R 5
# define HASHI 6

typedef struct s_philosopher	t_philo;

typedef struct s_data_philo
{
	int long		start_time;
	int				nb_philos;
	int				limit_time_to_die;
	int				limit_time_to_eat;
	int				limit_time_to_sleep;
	bool			has_meals_counter;
	int				how_many_meals;
	pthread_mutex_t	*cutlery;
	t_philo			*table;
	// pthread_mutex_t	print;
}	t_data;

typedef struct s_philosopher
{
	int					philo_id;
	pthread_t			table_id;
	long int			time_eat;
	int					nb_meals;
	pthread_mutex_t		*l_hashi;
	pthread_mutex_t		*r_hashi;
	t_data				*data;
}	t_philo;

bool		input_checker(int argc, char **argv);
t_data		init_data(int argc, char **argv);
long		ft_atol(const char *str);
int long	get_current_time(void);
int long	time_stamp(t_data *data);
void		print_message(t_philo *philo, int flag);
void		resting(t_philo *philo, int long must_wait);
void		*routine(void *arg);
void		dead(t_philo *philo);

#endif
