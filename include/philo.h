/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:07:40 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/14 12:54:30 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*									<MACROS>								*/
/* ************************************************************************** */

# define NC "\e[0m"
# define YELLOW "\e[1;33m"

/* ************************************************************************** */
/*									<STRUCTS>								*/
/* ************************************************************************** */

typedef struct s_counter
{
	size_t			count;
	pthread_mutex_t	count_mutex;
}					t_counter;

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
	struct s_philos	*philos;
}					t_table;

/* ************************************************************************** */
/*									<PROTOTYPES>								*/
/* ************************************************************************** */

/*	utils.c	*/
long				ft_atol(char *str);
int					only_digits(char **argv);
void				ft_exit(void *to_free, char *msg);
/*	logs.c	*/
void				print_data(t_table *tab);

/* ************************************************************************** */
/*									<\PROTOTYPES>								*/
/* ************************************************************************** */
#endif