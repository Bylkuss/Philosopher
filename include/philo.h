/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:07:40 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/09 12:45:34 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_philos
{
	pthread_t		thread;
	size_t			id;
	size_t			times_ate;
	size_t			time_to_die;
	struct s_table	*table;
}					t_philos;

typedef struct s_table
{
	size_t			n_thread;
	size_t			philos_nb;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			repeat_time;
	time_t			time_begin;
	struct s_philos		*philos;
}					t_table;

/* ************************************************************************** */
/*									<PROTOTYPES>							  */
/* ************************************************************************** */

/*	utils.c	*/
long	ft_atol(char *str);
int     only_digits(char **argv);
/*	logs.c	*/
void    print_data(t_table *tab);

/* ************************************************************************** */
/*									<\PROTOTYPES>							  */
/* ************************************************************************** */
#endif