/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:00:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/05/17 17:00:29 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	if(argc != 6)
	{
		printf("\033[33m Correct Input \033[0m\n");
		printf("\t🔢 PHILOS, ⌛ DIE, ⌛ EAT, ⌛ SLEEP, 🍴 MUST EAT\n");
	}
	(void)argv;
}