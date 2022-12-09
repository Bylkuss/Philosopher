/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:15:20 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/09 13:00:43 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#define NC "\e[0m"
#define YELLOW "\e[1;33m"

/*
void* routine(int *i_value)
{
    // t_table *table;
    // table = (t_table *)args;
    // table->philo_nb = 1;
    int i = (int *)i_value;
    printf("Message from thread nb %d\n", i[0]);
    i++;
    return 0;
}
*/

void init_vars(char **argv, t_table *tab)
{
    tab->philos = malloc(sizeof(t_philos));
    tab->philos_nb = ft_atol(argv[1]);
    tab->philos->time_to_die = ft_atol(argv[2]);
    tab->time_to_eat = ft_atol(argv[3]);
    tab->time_to_sleep = ft_atol(argv[4]);
    tab->repeat_time = INT_MAX;
    if (argv[5])
        tab->repeat_time = ft_atol(argv[5]);
    print_data(tab);
}

int main(int argc, char **argv)
{
    t_table tab;
    if (argc <= 6 && argc >= 5)
    {
        if (only_digits(&argv[1]) == 0)
        {
            printf("Args format not accepted!\n");
            return (0);
        }
        init_vars(argv, &tab);
        free(tab.philos);
    }
    else
        printf("Please insert args as follow: [int] [int] [int] [int] [int (optional)]\n");
    return (0);
}
