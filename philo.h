/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:24 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/30 15:56:05 by edribeir      ########   odam.nl         */
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
	int long		start_time;
	bool			is_alive;
	int				nb_philos;
	int				limit_time_to_die;
	int				limit_time_to_eat;
	int				limit_time_to_sleep;
	int				full_belly;
	bool			has_meals_counter;
	int				how_many_meals;
	pthread_mutex_t	*cutlery;
	t_philo			*philo;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t alive_lock;
}	t_table;

typedef struct s_philosopher
{
	int					philo_id;
	pthread_t			table_id;
	int					nb_meals;
	long int			last_meal;
	pthread_mutex_t		*l_hashi;
	pthread_mutex_t		*r_hashi;
	t_table				*table;
}	t_philo;

// Checker
bool		input_checker(int argc, char **argv);

// Init
t_table		init_table(int argc, char **argv);
void		init_philo(t_table *table);

//Threads
void		creating_philo_thread(t_table *table);
void		waiting_threads(t_table *table, pthread_t watcher);
void		supervisor(t_table *table, pthread_t *watcher);

void		resting(int long must_wait);
void		*routine(void *arg);
bool		had_enough_meals(t_table *table);
bool		is_starved(t_philo *philo);
bool		is_someone_dead(t_table *table);

// Utils
long		ft_atol(const char *str);
int long	get_current_time(void);
int long	time_stamp(t_table *table);
void		print_message(t_philo *philo, int flag);

#endif
