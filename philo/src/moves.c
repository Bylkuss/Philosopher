/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:42 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/25 19:13:45 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**

	* @brief Takes chops one after the other and taking the time needed to eat then dropping the chops
 * 
 * @param table The table struct
 * @param i The index of the philo
 * @return true if all well
 * @return false incase of an error
 */
bool	eat(t_table *table, t_philos *philo)
{
	if (repeat_time(table) == false)
		return (false);
	pthread_mutex_lock(&table->m_repeat_time);
	table->stop--;
	pthread_mutex_unlock(&table->m_repeat_time);
	pthread_mutex_lock(&table->m_philo_data);
	if (!table->time_begin)
		table->time_begin = get_time();
	philo->time_to_die = get_time();
	pthread_mutex_unlock(&table->m_philo_data);
	pthread_mutex_lock(&table->chopsticks[philo->chops.left]);
	if (!print_output(table, philo->id, BBLUE, CHOPSTICK1))
		return (false);
	pthread_mutex_lock(&table->chopsticks[philo->chops.right]);
	if (!print_output(table, philo->id, BBLUE, CHOPSTICK2))
		return (false);
	if (!print_output(table, philo->id, BGREEN, EATING))
		return (false);
	create_delay(table->time_to_eat);
	drop_chops(table, philo);
	return (true);
}

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
	time_t	time;
	time_t	akud;

	// time_t	ultimatum;
	pthread_mutex_lock(&table->m_philo_data);
	akud = time_range(table->time_begin);
	time = time_range(philo->time_to_die);
	// ultimatum = (time_t)table->ultimatum;
	if (time > (time_t)table->ultimatum)
	{
		pthread_mutex_unlock(&table->m_philo_data);
		pthread_mutex_lock(&table->m_dead);
		table->is_philos_dead = true;
		pthread_mutex_unlock(&table->m_dead);
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", BRED, akud, philo->id, DEAD, RESET);
		pthread_mutex_unlock(&table->writing_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->m_philo_data);
	// if(!repeat_time(table))
	// 	return (false);
	return (false);
}

bool	repeat_time(t_table *table)
{
	pthread_mutex_lock(&table->m_repeat_time);
	if (table->repeat_time > 0 && table->stop <= 0)
	{
		pthread_mutex_unlock(&table->m_repeat_time);
		return (false);
	}
	pthread_mutex_unlock(&table->m_repeat_time);
	return (true);
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
	// pthread_mutex_lock(&table->m_repeat_time);
	// table->stop--;
	// pthread_mutex_unlock(&table->m_repeat_time);
	if (pthread_mutex_unlock(&table->chopsticks[philo->chops.right]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[philo->chops.left]))
		return (false);
	return (true);
}
