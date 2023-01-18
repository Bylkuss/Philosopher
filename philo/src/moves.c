/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:53:38 by loadjou            #+#    #+#             */
/*   Updated: 2023/01/13 13:21:19 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

bool eat(t_table *table, size_t i)
{
	if (pthread_mutex_lock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	if (!print_output(table, table->philos[i].id, BLUE, CHOPSTICK1))
		return (false);
	if (pthread_mutex_lock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	if (!print_output(table, table->philos[i].id, BLUE, CHOPSTICK2))
		return (false);
	if (!print_output(table, table->philos[i].id, GREEN, EATING))
		return (false);
	table->philos[i].time_to_die = get_time();
	create_delay(table->time_to_eat);
	drop_chops(table, i);
	return (true);
}

bool go_to_sleep(t_table *table, size_t i)
{
	if (!print_output(table, table->philos[i].id, YELLOW, SLEEPING))
		return (false);
	create_delay(table->time_to_sleep);
	return (true);
}

bool think(t_table *table, size_t i)
{
	size_t akud;

	if (table->is_philos_dead == false)
	{

		akud = time_range(table->time_begin);
		pthread_mutex_lock(&table->writing_lock);
		printf("%s%-10ld %-3zu %-30s%s\n", GRAY, akud, table->philos[i].id,
			   THINKING, DEFAULT);
		pthread_mutex_unlock(&table->writing_lock);
		return (true);
	}
	return (false);
}

bool is_philo_dead(t_table *table, size_t i)
{
	time_t time;
	time_t akud;

	akud = time_range(table->time_begin);
	time = time_range(table->philos[i].time_to_die);
	if (time > (time_t)table->ultimatum)
	{
		pthread_mutex_lock(&table->writing_lock);

		printf("%s%-10ld %-3zu %-30s%s\n", RED, akud, table->philos[i].id,
			   DEAD, DEFAULT);
		pthread_mutex_unlock(&table->writing_lock);

		table->is_philos_dead = true;

		return (true);
	}
	return (false);
}

bool drop_chops(t_table *table, size_t i)
{
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.left]))
		return (false);
	if (pthread_mutex_unlock(&table->chopsticks[table->philos[i].chops.right]))
		return (false);
	if (table->philos[i].times_ate)
		table->philos[i].times_ate--;
	return (true);
}
