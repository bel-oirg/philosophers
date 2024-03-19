/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:41:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/19 05:06:25 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philog(t_philo *philo, const char *action)
{
	long long	interval;
	long long	start;
	int			id;

	if (philo->table->philo_down || philo->table->full)
		return ;
	interval = 0;
	id = philo->id;
	start = philo->table->start;
	interval = time_now() - start;
	pthread_mutex_lock(&(philo->table->log));
	printf("%lld %d %s\n", interval, id, action);
	if (!philo->table->philo_down)
		pthread_mutex_unlock(&(philo->table->log));
		
}

int	smart_sleep(long interval, t_table *table)
{
	long long	now;

	(void)table;
	now = time_now();
	while(time_now() - now <= interval)
	{
		if (table->philo_down || table->full)
			return (1);
		usleep(50);
	}
	return (0);
}
