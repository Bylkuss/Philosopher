/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:42 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/27 11:24:41 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**

	* @brief Takes chops one after the other and taking the time needed
			to eat then dropping the chops
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false incase of an error
 */
bool	eat(t_table *table, t_philos *philo)
{
	if (!repeat_time(table))
		return (false);
	pthread_mutex_lock(&table->m_repeat_time);
	table->stop--;
	pthread_mutex_unlock(&table->m_repeat_time);
	if (repeat_time(table) == false)
		return (false);
	pthread_mutex_lock(&table->chopsticks[philo->chops.left]);
	if (!print_output(table, philo->id, BBLUE, CHOPSTICK1))
		return (false);
	pthread_mutex_lock(&table->chopsticks[philo->chops.right]);
	if (!print_output(table, philo->id, BBLUE, CHOPSTICK2))
		return (false);
	pthread_mutex_lock(&philo->m_last_time_eat);
	philo->last_time_eat = get_time() - table->time_begin;
	pthread_mutex_unlock(&philo->m_last_time_eat);
	if (!print_output(table, philo->id, BGREEN, EATING))
		return (false);
	create_delay(table->time_to_eat);
	drop_chops(table, philo);
	return (true);
}

/*
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation
	should stop when every philosopher
has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die
*/

/**
 * @brief Put the philosopher to sleep.
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false if any error
 */
bool	go_to_sleep(t_table *table, t_philos *philo)
{
	if (!print_output(table, philo->id, BYEL, SLEEPING))
		return (false);
	create_delay(table->time_to_sleep);
	return (true);
}

/**
 * @brief Thinking for a philo. Print it.
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false if any error
 */
bool	think(t_table *table, t_philos *philo)
{
	time_t	akud;
	size_t	is_dead;

	pthread_mutex_lock(&table->m_dead);
	is_dead = table->is_philos_dead;
	pthread_mutex_unlock(&table->m_dead);
	if (is_dead)
		return (false);
	pthread_mutex_lock(&table->m_philo_data);
	akud = time_range(table->time_begin);
	pthread_mutex_unlock(&table->m_philo_data);
	pthread_mutex_lock(&table->writing_lock);
	printf("%s%-10ld %-3zu %-30s%s\n", BMAG, akud, philo->id, THINKING, RESET);
	pthread_mutex_unlock(&table->writing_lock);
	return (true);
}

/**
 * @brief Check if the philo is dead or not
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if the philo is dead
 * @return false if the philo is alive
 */
bool	is_philo_dead(t_table *table, t_philos *philo)
{
	time_t	akud;
	time_t	diego;

	pthread_mutex_lock(&philo->m_last_time_eat);
	akud = time_range(table->time_begin);
	diego = get_time();
	if (((size_t)(get_time() - table->time_begin)
		- philo->last_time_eat) > table->ultimatum)
	{
		pthread_mutex_lock(&table->m_dead);
		table->is_philos_dead = true;
		pthread_mutex_unlock(&table->m_dead);
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BRED, akud, philo->id, DEAD, RESET);
		pthread_mutex_unlock(&table->writing_lock);
		pthread_mutex_unlock(&philo->m_last_time_eat);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_last_time_eat);
	return (false);
}

/**
 * @brief Drop the chops right and left
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if the philo is dead
 * @return false if the philo is alive
 */
bool	drop_chops(t_table *table, t_philos *philo)
{
	if (pthread_mutex_unlock(&table->chopsticks[philo->chops.right]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[philo->chops.left]))
		return (false);
	return (true);
}
