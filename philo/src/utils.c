/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:03:21 by loadjou            #+#    #+#             */
/*   Updated: 2022/12/18 11:12:13 by loadjou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

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

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	time_range(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	create_delay(time_t time)
{
	usleep(time * 1000);
}

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
