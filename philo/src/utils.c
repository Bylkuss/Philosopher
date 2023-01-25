/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:03:21 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/19 16:09:37 by hsaadi           ###   ########.fr       */
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

/**
 * @brief Sleep for a certain time
 * 
 * @param time_to_stop The time to stop
 */
void	ft_sleep(long int time_to_stop)
{
	long int	delay;

	while (1)
	{
		delay = time_to_stop - get_time();
		if (delay <= 0)
			break ;
		usleep(50);
	}
}
