/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:13:37 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/27 11:01:50 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Calculate's the length of an str
 * 
 * @param str The string to count
 * @return size_t the count
 */
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Print an error message
 * 
 * @param str The message error
 * @return true If done right
 * @return false if something wrong
 */
bool	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(2, "\n", 1);
	return (false);
}

/**
 * @brief printout the status and the timestamp 
 * 
 * @param table The table struct to use
 * @param id The philosopher's index
 * @param color The color of the output in the terminal
 * @param status The status of the philo you want to printout
 * @return true If everything went well
 * @return false if something went wrong
 */
bool	print_output(t_table *table, size_t id, char *color, char *status)
{
	time_t	present;
	size_t	is_dead;

	present = time_range(table->time_begin);
	pthread_mutex_lock(&table->m_dead);
	is_dead = table->is_philos_dead;
	pthread_mutex_unlock(&table->m_dead);
	if (is_dead)
		return (false);
	pthread_mutex_lock(&table->writing_lock);
	printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, RESET);
	pthread_mutex_unlock(&table->writing_lock);
	return (true);
}

/**
 * @brief Free the chops and the philos
 * 
 * @param table 
 */
void	philos_free(t_table *table)
{
	free(table->chopsticks);
	free(table->philos);
}
