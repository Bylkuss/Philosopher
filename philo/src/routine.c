/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:55:13 by loadjou            #+#    #+#             */
/*   Updated: 2023/01/13 12:03:00 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *args)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)args;
	i = table->n_thread;
	if (table->repeat_time)
	{
		while (table->philos[i].times_ate && !table->is_philos_dead)
			run_routine(table, i);
	}
	else
	{
		while (!table->is_philos_dead)
		{
			if (!run_routine(table, i))
				break ;
		}
	}
	return (NULL);
}

size_t	run_routine(t_table *table, size_t i)
{
	if (!eat(table, i))
		return (false);
	if (!go_to_sleep(table, i))
		return (false);
	if (!think(table, i))
		return (false);
	return (true);
}

void	*maestro_routine(void *args)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)args;
	i = 0;
	if (table->philos[i].times_ate)
	{
		while (table->philos[i].times_ate && !table->is_philos_dead)
		{
			if (is_philo_dead(table, i))
				break ;
		}
	}
	else
	{
		while (!table->is_philos_dead)
		{
			if (is_philo_dead(table, i))
				break ;
		}
	}
	return (NULL);
}
