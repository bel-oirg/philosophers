/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:41:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/13 05:37:49 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philog(long long start, int id, const char *action)
{
	long long	interval;
	
	interval = time_now() - start;
	printf("%lld %d %s\n", interval, id, action);
}

void	smart_sleep(long interval)
{
	long long	now;

	now = time_now();
	while(time_now() - now < interval)
		usleep(50);
}

// int none_dead(t_table *table)
// {
// 	t_philo *philo;
// 	int 	index;

// 	index = -1;
// 	philo = table->philo;
// 	while(++index < table->philos)
// 		if (philo[index].is_dead)
// 			return (0);
// 	return (1);
// }
