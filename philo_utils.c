/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:41:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/28 03:49:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_death(void *philo_raw)
{
	long long	fasting;
	t_table		*table;
	t_philo		*philo;
	int			index;

	philo = (t_philo *)philo_raw;
	table = philo->table;
	while (1)
	{
		fasting = time_now() - philo->last_meal;
		if (fasting > table->ttd)
		{
			philog(philo, DEAD);
			index = -1;
			while (++index < table->philos)
				if (sem_post(philo->table->the_end) == -1)
					err_w("Sem post failed - the_end");
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	begin(t_philo *philo)
{
	pthread_t	monitor_th;
	t_table		*table;

	table = philo->table;
	philo->last_meal = time_now();
	if (pthread_create(&monitor_th, NULL, check_death, philo))
		err_w("Failed to create a thread - monitor_th");
	if (pthread_detach(monitor_th))
		err_w("Failed to detach a thread - monitor_th");
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		ft_eat(philo);
		if (philo->eated == table->meals)
		{
			if (sem_post(table->the_end) == -1)
				err_w("Sem post failed - the_end");
			exit(0);
		}
		ft_sleep(philo);
		ft_think(philo);
	}
}

void	philog(t_philo *philo, const char *action)
{
	long long	interval;
	long long	start;
	int			id;

	id = philo->id;
	start = philo->table->start;
	interval = time_now() - start;
	if (sem_wait((philo->table->log)))
		err_w("Failed to wait a semaphore - log");
	if (!philo->table->philo_down)
		printf("%lld %d %s\n", interval, id, action);
	if (*action == 'd')
	{
		philo->table->philo_down = 1;
		return ;
	}
	if (sem_post((philo->table->log)))
		err_w("Sem post failed - log");
}

void	smart_sleep(long interval, t_table *table)
{
	long long	now;

	now = time_now();
	while (time_now() - now <= interval)
		usleep(table->philos * 2);
}

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
