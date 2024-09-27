/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:24 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/27 17:49:44 by edribeir      ########   odam.nl         */
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
# define FULL 7

typedef struct s_philosopher	t_philo;

typedef struct s_data_philo
{
	int				nb_philos;
	int				limit_time_to_die;
	int				limit_time_to_eat;
	int				limit_time_to_sleep;
	int				full_belly;
	bool			has_meals_counter;
	int				how_many_meals;
	pthread_mutex_t	*cutlery;
	t_philo			*table;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	int long		start_time;
}	t_data;

typedef struct s_philosopher
{
	bool				is_alive;
	int					philo_id;
	pthread_t			table_id;
	int					nb_meals;
	long int			last_meal;
	pthread_mutex_t		*l_hashi;
	pthread_mutex_t		*r_hashi;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	t_data				*data;
}	t_philo;

// Checker
bool		input_checker(int argc, char **argv);

// Init
t_data		init_data(int argc, char **argv);
void		init_table(t_data *data);

//Threads
void		creating_philo_thread(t_data *data);
void		waiting_threads(t_data *data, pthread_t watcher);
void		supervisor(t_data *data, pthread_t *watcher);

void		resting(int long must_wait);
void		*routine(void *arg);
bool		had_enough_meals(t_data *data);
bool		is_starved(t_philo *philo);
bool		is_someone_dead(t_data *data);

// Utils
long		ft_atol(const char *str);
int long	get_current_time(void);
int long	time_stamp(t_data *data);
void		print_message(t_philo *philo, int flag);

#endif
