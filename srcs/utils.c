/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:56:38 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/09 12:46:14 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int     only_digits(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		// printf("%s\n", argv[i]);
		j = 0;
		while (argv[i][j++])
            if (!((argv[i][j] >= '0' && argv[i][j] <= '9') || (argv[i][j] == ' ')))
				return (0);
        i++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	long			i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}