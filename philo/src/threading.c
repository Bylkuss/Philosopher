/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by loadjou            #+#    #+#             */
/*   Updated: 2023/01/12 18:25:51 by loadjou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#include "../include/philo.h"

bool	threading(t_table *table)
{
	size_t	i;

	i = 0;
	table->time_begin = get_time(); // + (table->philos_nb * 2 * 10);
	while (i < table->philos_nb)
	{
		table->n_thread = i;
		// start_some_delay(table->time_begin);
		
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				(void *)table))
			return (false);
		i++;
		// usleep(10);
	}
	if (pthread_create(&table->maestro, NULL, &maestro_routine, (void *)table))
		return (false);
	if (!joining_threads(table))
		return (false);
	return (true);
}

bool	joining_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nb)
	{
		if (table->philos[i].times_ate == 0)
		{
			if (pthread_detach(table->philos[i].thread))
				return (false);
		}
		else if (table->philos[i].times_ate)
		{
			if (pthread_join(table->philos[i].thread, NULL))
				return (false);
		}
		i++;
	}
	if (pthread_join(table->maestro, NULL))
		return (false);
	return (true);
}

bool	destroying_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nb)
	{
		pthread_mutex_destroy(&table->chopsticks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->writing_lock);
	return (true);
}
