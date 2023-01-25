/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:48:10 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/25 15:20:28 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Create and manage threads for philosophers and maestro
 *

	* This function takes in a pointer to a table and creates threads for each philosopher

	* and the maestro using pthread_create and assigns the routine function for the philosophers
 * and maestro_routine function for the maestro.

	* It also calls joining_threads function to wait for all threads to complete before returning.
 *
 * @param table Pointer to the table structure
 * @return true if thread creation and management is successful
 * @return false if thread creation or joining fails
 */

bool	threading(t_table *table)
{
	size_t	i;

	i = 0;
	// table->time_begin = get_time();
	if (pthread_mutex_init(&table->m_philo_id, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->m_philo_data, NULL) != 0)
		return (false);
	while (i < table->philos_nb)
	{
		pthread_mutex_lock(&table->m_philo_id);
		table->n_thread = i;
		pthread_mutex_unlock(&table->m_philo_id);
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				(void *)table))
			return (false);
		i++;
	}
	if (pthread_create(&table->maestro, NULL, &maestro_routine, (void *)table))
		return (false);
	if (!joining_threads(table))
		return (false);
	return (true);
}

/**
 * @brief Wait for all threads to complete
 *

	* This function takes in a pointer to a table and waits for all philosopher threads
 * and maestro thread to complete using pthread_join.
 *
 * @param table Pointer to the table structure
 * @return true if all threads are successfully joined
 * @return false if any thread fails to join
 */

bool	joining_threads(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nb)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (false);
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
