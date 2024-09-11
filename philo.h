/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:24 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/11 17:17:46 by eduarda       ########   odam.nl         */
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

# define RED "\033[31m"
# define GREEN "\033[32m"
# define CYAN "\033[36m"
# define PINK "\033[35m"
# define YEL "\033[0;33m"
# define RESET "\033[0m"

bool	input_checker(int argc, char **argv);

#endif
