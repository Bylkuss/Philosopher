/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:57 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/25 19:13:59 by loadjou          ###   ########.fr       */
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
	t_table	*table;
	size_t	i;

	table = (t_table *)args;
	pthread_mutex_lock(&table->m_philo_id);
	i = table->n_thread;
	pthread_mutex_unlock(&table->m_philo_id);
	// if (i % 2 == 0)
	// 	usleep(20);
	while (1)
	{
		if (!eat(table, &table->philos[i]))
		{
			drop_chops(table, &table->philos[i]);
			return (false);
		}
		if (!go_to_sleep(table, &table->philos[i]))
			return (false);
		if (!think(table, &table->philos[i]))
			return (false);
	}
	return (NULL);
}

/**

	* @brief The routine the maestro should run to check if any other philo is dead or should die!
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
	pthread_mutex_lock(&table->m_philo_data);
	nb_philos = table->philos_nb;
	pthread_mutex_unlock(&table->m_philo_data);
	while (repeat_time(table))
	{
		// if(!repeat_time(table))
		// 	break ;
		if (i == nb_philos - 1)
			i = 0;
		if (is_philo_dead(table, &table->philos[i]))
			return (NULL);
		i++;
	}
	return (NULL);
}
