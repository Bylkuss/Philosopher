/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:41:30 by loadjou           #+#    #+#             */
/*   Updated: 2023/01/17 22:45:52 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	msg_error(char *str)
{
	write(2, &(*str), ft_strlen(str));
	write(2, "\n", 1);
	return (false);
}

bool	print_output(t_table *table, size_t id, char *color, char *status)
{
	time_t	present;

	present = time_range(table->time_begin);
	pthread_mutex_lock(&table->writing_lock);
	if (table->is_philos_dead)
	{
		pthread_mutex_unlock(&table->writing_lock);
		return (false);
	}
	else
		printf("%s%-10ld %-3zu %-30s%s\n", color, present, id, status, DEFAULT);
	pthread_mutex_unlock(&table->writing_lock);
	return (true);
}

void	philos_free(t_table *table)
{
	free(table->chopsticks);
	free(table->philos);
}

void	start_some_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}
