/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:57 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/27 12:08:01 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief The routine each philo should run
 * 
 * @param args The address of the struct to use 
 * @return void* 
 */
void	*routine(void *args)
{
	t_philos	*philo;
	t_table		*table;

	philo = (t_philos *)args;
	table = philo->table;
	if (philo->id % 2 == 0)
	{
		usleep(500);
	}
	while (1)
	{
		if (!eat(table, philo))
		{
			drop_chops(table, philo);
			return (false);
		}
		if (!go_to_sleep(table, philo))
			return (false);
		if (!think(table, philo))
			return (false);
	}
	return (NULL);
}

/**

	* @brief The routine the maestro should run to check if any other philo is dead
		or should die!
 * 
 * @param args The address of the struct to use 
 * @return void* 
 */
void	*maestro_routine(void *args)
{
	t_table	*table;
	size_t	i;
	size_t	nb_philos;

	table = (t_table *)args;
	i = 0;
	nb_philos = table->philos_nb;
	while (1)
	{
		if (!repeat_time(table))
			break ;
		if (i == nb_philos - 1)
			i = 0;
		if (is_philo_dead(table, &table->philos[i]))
			return (NULL);
		i++;
	}
	return (NULL);
}
