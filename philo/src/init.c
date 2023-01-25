/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:00:49 by hsaadi            #+#    #+#             */
/*   Updated: 2023/01/25 16:16:46 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Manages one philosopher's life cycle
 *

	* This function takes in a pointer to a table and simulates the life cycle of a philosopher.

	* It starts by getting the current time and storing it in the time_begin variable.
 * Then it locks the left chopstick associated with the first philosopher,
 * prints a message indicating that the philosopher is eating,
 * creates a delay for a certain amount of time,
 * prints a message indicating that the philosopher is dead,
 * unlocks the chopstick and sets the is_philos_dead variable to true.
 *
 * @param table Pointer to the table structure
 * @return false
 */

static bool	manage_one_philo(t_table *table)
{
	time_t	present;

	present = 0;
	table->time_begin = get_time();
	pthread_mutex_lock(&table->chopsticks[table->philos[0].chops.left]);
	printf("%s%-10ld %-3zu %-30s%s\n", BBLUE, present, table->philos[0].id,
			CHOPSTICK1, RESET);
	create_delay(table->ultimatum);
	present = time_range(table->time_begin);
	printf("%s%-10ld %-3zu %-30s%s\n", BRED, present, table->philos[0].id, DEAD,
			RESET);
	pthread_mutex_unlock(&table->chopsticks[table->philos[0].chops.left]);
	table->is_philos_dead = true;
	return (false);
}

/**
 * @brief Initialize chopsticks for the table
 * 
	* This function takes in a pointer to a table and allocates memory for the chopsticks and initializes them 
	* using pthread_mutex_init. It also initializes the writing_lock using pthread_mutex_init.
 *
 * @param table Pointer to the table structure
 * @return true if initialization is successful
 * @return false if memory allocation or mutex initialization fails
 */
static bool	init_chops(t_table *table)
{
	size_t	i;

	table->chopsticks = malloc(sizeof(pthread_mutex_t) * table->philos_nb);
	if (table->chopsticks == NULL)
		return (msg_error(ERRMAL));
	i = 0;
	while (i < table->philos_nb)
	{
		if (pthread_mutex_init(&table->chopsticks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&table->writing_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->m_dead, NULL) != 0)
		return (false);
	return (true);
}

/**
 * @brief Initialize philosophers and chopsticks for the table
 * 

	* This function takes in a pointer to a table and allocates memory for the philosophers and chopsticks,
	
 * initializes the philosophers' id and times_ate,
	and assigns left and right chopsticks to each philosopher.
 *
 * @param table Pointer to the table structure
 * @return true if initialization is successful
 * @return false if memory allocation fails
 */
static bool	init_philos(t_table **table)
{
	size_t	i;
	size_t	j;

	(*table)->philos = malloc(sizeof(t_philos) * ((*table)->philos_nb + 1));
	if (!(*table)->philos)
		return (msg_error(ERRMAL));
	i = 0;
	j = 1;
	if (!init_chops(*table))
		return (msg_error(ERRMAL));
	while (i < (*table)->philos_nb)
	{
		(*table)->philos[i].id = i + 1;
		(*table)->philos[i].times_ate = (*table)->repeat_time;
		(*table)->philos[i].chops.left = i;
		if (i == (*table)->philos_nb - 1)
			(*table)->philos[i].chops.right = 0;
		else
			(*table)->philos[i].chops.right = j++;
		i++;
	}
	if(pthread_mutex_init(&(*table)->m_repeat_time, NULL) != 0)
		return false;
	return (true);
}

/**
*@brief Initialize the table struct with values passed as command line arguments.
* The function sets the number of philosophers to either the value passed as an argument or a maximum of 200,
	assigns values to other table properties such as ultimatum, time to eat,
	and time to sleep. It also checks for errors in the arguments passed and initializes the philosophers.
If the number of philosophers is one,
	it calls a separate function to manage the single philosopher.
Overall,this function sets up the table and philosophers for the program to run.
*@param argc The number of arguments passed
*@param argv The array of arguments passed
*@param table The table struct to be initialized
*@return true If initialization is successful
*@return false If initialization fails
*/

bool	init_table(size_t argc, char **argv, t_table *table)
{
	if (ft_atol(argv[1]) > 200)
		table->philos_nb = 200;
	else
		table->philos_nb = ft_atol(argv[1]);
	table->ultimatum = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->time_begin = 0;
	if (argv[5])
		table->repeat_time = ft_atol(argv[5]);
	else 
		table->repeat_time = -1;
	table->stop = table->philos_nb * table->repeat_time;
	if (!print_args_errors(table, argc))
		return (false);
	if (!init_philos(&table))
		return (false);
	table->is_philos_dead = false;
	if (table->philos_nb == 1)
		manage_one_philo(table);
	return (true);
}
