/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 10:34:01 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/23 22:57:16 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int long	ft_atol(const char *str)
{
	int			i;
	int long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result);
}

static bool	number_validation(char **argv)
{
	int	i;

	i = 2;
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		return (false);
	while (argv[i])
	{
		if (ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > INT_MAX
			|| ft_atol(argv[i]) < 60)
		{
			if (ft_atol(argv[i]) < 60)
				printf(RED"\t\tTime must be bigger than 60!\n"RESET);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	digit_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	input_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (false);
	if (digit_checker(argv) == false)
		return (false);
	if (number_validation(argv) == false)
		return (false);
	return (true);
}
