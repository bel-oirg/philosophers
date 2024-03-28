/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:41:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/27 21:51:14 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo(t_table *table)
{
	t_philo	*philo;
	int		index;
	char	*indexed;

	index = -1;
	philo = table->philo;
	while (++index < table->philos)
	{
		kill(table->philo[index].pid_id, SIGKILL);
		sem_close(table->forks[index]);
		indexed = itoa(index);
		sem_unlink(indexed);
		free(indexed);
	}
	sem_close(table->log);
	sem_unlink("sem_log");
	sem_close(table->the_end);
	sem_unlink("sem_the_end");
}

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

	id = philo->id;
	start = philo->table->start;
	interval = time_now() - start;
	if (sem_wait((philo->table->log)))
		err_w("Failed to wait a semaphore");
	if (!philo->table->philo_down)
		printf("%lld %d %s\n", interval, id, action);
	if (*action == 'd')
	{
		philo->table->philo_down = 1;
		return ;
	}
	if (sem_post((philo->table->log)))
		err_w("Sem post failed");
}

void	smart_sleep(long interval, t_table *table)
{
	long long	now;

	now = time_now();
	while (time_now() - now <= interval)
		usleep(table->philos * 2);
}
