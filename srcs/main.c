/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:15:20 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/14 15:39:18 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"



/*
int ph=*(int *)n;
printf("Philosopher %d wants to eat\n",ph);
printf("Philosopher %d tries to pick left chopstick\n",ph);
sem_wait(&chopstick[ph]);
printf("Philosopher %d picks the left chopstick\n",ph);
printf("Philosopher %d tries to pick the right chopstick\n",ph);
sem_wait(&chopstick [(ph+1) %5]);
printf("Philosopher %d picks the right chopstick\n",ph);
eat (ph);
sleep (2);
printf("Philosopher %d has finished eating\n",ph);
sem_post(&chopstick [(ph+1) %5]);
printf("Philosopher %d leaves the right chopstick\n",ph);
sem_post(&chopstick[ph]);
printf("Philosopher %d leaves the left chopstick\n",ph);
*/

void *    routine(void *data)
{
    // int i = 0;
    int ph=*(int *)data;
    printf("Philosopher %d wants to eat\n",ph);
    printf("Philosopher %d tries to pick left chopstick\n",ph);
    printf("Philosopher %d picks the left chopstick\n",ph);
    printf("Philosopher %d tries to pick the right chopstick\n",ph);
    return NULL;
    
}

void    threading()
{
    pthread_t   pid[5];
    int i = 0;
    while(i < 5)
    {
        pthread_create(&pid[i], NULL, &routine, NULL);
        i++;
    }
    i = 0;
    while(i++ < 5)
        pthread_join(pid[i], NULL);
}

void init_vars(char **argv, t_table *tab)
{
    tab->philos_nb = ft_atol(argv[1]);
    tab->philos->time_to_die = ft_atol(argv[2]);
    tab->time_to_eat = ft_atol(argv[3]);
    tab->time_to_sleep = ft_atol(argv[4]);
    tab->repeat_time = INT_MAX;
    if (!argv[5] || ft_atol(argv[5]) > 200)
        tab->repeat_time = 200;
    else
        tab->repeat_time = ft_atol(argv[5]);
    tab->philos = calloc(sizeof(t_philos), tab->philos_nb);
    if(!tab->philos)
        ft_exit(tab->philos, "Error while trying to malloc struct\n");
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
        printf("Hey\n");
        (void) tab;
        // init_vars(argv, &tab);
        threading();
        // free(tab.philos);
    }
    else
        printf("Please insert args as follow: [int] [int] [int] [int] [int (optional)]\n");
    return (0);
}

