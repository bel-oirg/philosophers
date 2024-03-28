/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:53:08 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/27 21:26:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	num;
	int		sign;

	while (*str == ' ' || *str == '\t')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	num = 0;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	if (sign * num < 0)
		err_w("Enter positive values");
	return (sign * num);
}

char	*itoa(int index)
{
	char	*out;
	int		counter;

	counter = 1;
	while (index / 10)
	{
		counter++;
		index /= 10;
	}
	out = malloc(counter + 1);
	if (!out)
		err_w("Malloc failed to allocate");
	out[counter] = 0;
	while (--counter >= 0)
	{
		out[counter] = index % 10 + '0';
		index /= 10;
	}
	return (out);
}

static void	init_semaphores(t_table *table)
{
	int		index;
	char	*indexed;

	index = -1;
	while (++index < table->philos)
	{
		indexed = itoa(index);
		sem_unlink(indexed);
		table->forks[index] = sem_open(indexed, O_CREAT, 0644, 1);
		free(indexed);
		if (table->forks[index] == SEM_FAILED)
			err_w("Failed to open semaphore");
	}
	sem_unlink("sem_log");
	sem_unlink("sem_the_end");
	table->log = sem_open("sem_log", O_CREAT, 0644, 1);
	if (table->log == SEM_FAILED)
		err_w("Failed to open semaphore");
	table->the_end = sem_open("sem_the_end", O_CREAT, 0644, 0);
	if (table->the_end == SEM_FAILED)
		err_w("Failed to open semaphore");
}

void	init_philo(t_table *table, t_philo *p)
{
	long	philos;
	int		index;

	philos = table->philos;
	table->philo_down = 0;
	index = philos;
	init_semaphores(table);
	while (--index >= 0)
	{
		p[index].table = table;
		p[index].eated = 0;
		p[index].id = index + 1;
		p[index].r_fork = (table->forks[(index + 1) % philos]);
		p[index].l_fork = (table->forks[index]);
	}
	table->philo = p;
}
