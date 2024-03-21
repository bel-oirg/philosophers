/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:53:08 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/21 13:58:51 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(char *str)
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

int	init_philo(t_table *table, t_philo *p)
{
	long	philos;
	int		index;
	
	philos = table->philos;
	table->philo_down = 0;
	index = philos;
	while (--index >= 0)
	{
		if (pthread_mutex_init(&(table->forks[index]), NULL))
			return (err_w("Mutex failed to init"), 1);
		p[index].table = table;
		p[index].eated = 0;
		p[index].id = index + 1;
		p[index].r_fork = &(table->forks[(index + 1) % philos]);
		p[index].l_fork = &(table->forks[index]);
	}
	if (pthread_mutex_init(&(table->m_death), NULL))
		return (err_w("Mutex failed to init"), 1);
	if (pthread_mutex_init(&(table->log), NULL))
		return (err_w("Mutex failed to init"), 1);
	table->philo = p;
	return (0);
}

int	parse_args(char *argv[], t_table *table)
{
	table->philos = ft_atol(argv[1]);
	table->ttd = ft_atol(argv[2]);
	table->tte = ft_atol(argv[3]);
	table->tts = ft_atol(argv[4]);
	table->meals = -1;
	if (argv[5])
		table->meals = ft_atol(argv[5]);
	if (table->philos > 200)
		return (err_w("We have only 200 chairs"), 1);
	if (table->ttd < 60 || table->tte < 60 || table->tts < 60)
		return (err_w("Enter higher values"), 1);
	return (0);
}
