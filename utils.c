/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:44 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/28 03:43:24 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_w(char *str)
{
	printf("[-] %s\n", str);
	exit(1);
}

void	ft_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (sem_wait(table->forks))
		err_w("Failed to wait a semaphore - forks");
	philog(philo, FORK);
	if (table->philos == 1)
		return (smart_sleep(table->ttd, table));
	if (sem_wait(table->forks))
		err_w("Failed to wait a semaphore - forks");
	philog(philo, FORK);
	philog(philo, EAT);
	philo->last_meal = time_now();
	smart_sleep(philo->table->tte, philo->table);
	philo->eated++;
	if (sem_post(table->forks))
		err_w("Sem post failed - forks");
	if (sem_post(table->forks))
		err_w("Sem post failed - forks");
}

void	ft_sleep(t_philo *philo)
{
	philog(philo, SLEEP);
	smart_sleep(philo->table->tts, philo->table);
}

void	ft_think(t_philo *philo)
{
	philog(philo, THINK);
}

long long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
