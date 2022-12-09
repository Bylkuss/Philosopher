/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:19:22 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/09 12:24:40 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    print_data(t_table *tab)
{
    printf("philos_nb = %ld\ntime_to_die = %ld\ntime_to_eat = %ld\ntime_to_sleep = %ld\nrepeat_time = %ld\n", tab->philos_nb, tab->philos->time_to_die, tab->time_to_eat, tab->time_to_sleep, tab->repeat_time);
}