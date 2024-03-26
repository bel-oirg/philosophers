/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:34:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/25 19:52:24 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->meals < 0)
		return (0);
	if (philo->eated >= table->meals)
		table->philo_down = 1;
		// sem_wait(table->log),
	return (table->philo_down);
}

int check_death(t_philo *philo)
{
	long long	fasting;
	t_table		*table;

	table = philo->table;

	fasting = time_now() - philo->last_meal;
	if (fasting > philo->table->ttd)
	{
		philog(philo, DEAD);
		sem_wait(table->log);
		philo->table->philo_down = 1;
	}
	return (philo->table->philo_down);
}

void	destroy_philo(t_table *table)
{
	t_philo	*philo;
	int		index;

	// philo = philo->table->philo;
	index = -1;
	philo = table->philo;
	while(++index < table->philos)
		kill(table->philo[index].pid_id, SIGKILL),
		sem_close(table->forks[index]),
		sem_unlink(itoa(index));
	sem_close(table->log);
	sem_unlink("sem_log");
	sem_close(table->the_end);
	sem_unlink("sem_the_end");

		// pthread_mutex_destroy(&(table->forks[index]));
	// pthread_mutex_destroy(&(table->log));
	// pthread_mutex_destroy(&(table->m_death)); 
}
