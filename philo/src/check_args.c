/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:22:54 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/18 11:56:45 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Check if arguments are valid (Numbers)
 * 
 * @param argv The list of args to check 
 * @return true  if valid
 * @return false is not valid
 */
bool	args_are_valid(char **argv)
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
			{
				printf("%s%s\n", BRED, ERRARG);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Print out the errors 
 * 
 * @param table The structure that contains all the table's data
 * @param argc The number or args received
 * @return true if all well
 * @return false if any error
 */
bool	print_args_errors(t_table *table, size_t argc)
{
	if (!table->philos_nb || !table->ultimatum || !table->time_to_eat
		|| !table->time_to_sleep)
	{
		printf("%s%s\n", BRED, ERRARG);
		return (false);
	}
	if (argc == 6 && table->repeat_time <= 0)
	{
		printf("%s%s\n", BRED, ERRARG);
		return (false);
	}
	return (true);
}
