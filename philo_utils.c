/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:41:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/25 16:34:24 by bel-oirg         ###   ########.fr       */
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

	interval = 0;
	id = philo->id;
	start = philo->table->start;
	interval = time_now() - start;
	sem_wait((philo->table->log));
	(!philo->table->philo_down) && (printf("%lld %d %s\n", interval, id, action));
	if (*action == 'd')
		philo->table->philo_down = 1;
	sem_post((philo->table->log));
}

int	smart_sleep(long interval, t_table *table)
{
	long long	now;

	now = time_now();
	while(time_now() - now <= interval)
	{
		if (table->philo_down)
			return (1);
		usleep(table->philos * 2);
	}
	return (0);
}
