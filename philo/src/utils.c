/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:14:14 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/27 11:30:25 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief From an str return a long int 
 * 
 * @param st the string to use
 * @return size_t the long int to return 
 */
size_t	ft_atol(const char *str)
{
	size_t	i;
	size_t	num;
	size_t	sign;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

/**
 * @brief Get the time object
 * 
 * @return time_t 
 */
time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Calculate a time range from a certain given time
 * 
 * @param time The starting time
 * @return time_t The time range
 */
time_t	time_range(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

/**
 * @brief Create a delay for the specified (time)
 * @param time The delay
 */
// void	create_delay(time_t time)
// {
// 	usleep(time * 1000);
// }

void	create_delay(time_t time)
{
	time_t	delay;

	delay = get_time() + time;
	while (get_time() < delay)
		usleep(50);
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
