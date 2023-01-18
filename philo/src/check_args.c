/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:36:12 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/17 22:44:29 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

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
				printf("%s%s\n", RED, ERRARG);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	print_args_errors(t_table *table, size_t argc)
{
	if (!table->philos_nb || !table->ultimatum || !table->time_to_eat
		|| !table->time_to_sleep)
	{
		printf("%s%s\n", RED, ERRARG);
		return (false);
	}
	if (argc == 6 && table->repeat_time <= 0)
	{
		printf("%s%s\n", RED, ERRARG);
		return (false);
	}
	return (true);
}
