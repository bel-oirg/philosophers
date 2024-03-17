/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:34:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/17 09:33:50 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_philo *philo)
{
	int 	index;
	t_table	*table;

	philo = philo->table->philo;
	table = philo->table;
	index = -1;
	if (table->meals < 0)
		return (0);
	while(++index < table->philos)
	{
		if (philo[index].eated < table->meals)
			return (0);
	}
	return (1);
}

int check_death(t_philo *philo)
{
	long long fasting;

	fasting = time_now() - philo->last_meal;
	if (philo->table->philo_down || fasting > philo->table->ttd)
	{
		philo->table->philo_down = 1;
		philog(philo, DEAD);
		return (1);
	}
	return (0);
}

void	destroy_philo(t_table *table)
{
	t_philo	*philo;
	int		index;

	philo = table->philo;

	philo = philo->table->philo;
	index = -1;
	while(++index < table->philos)
		pthread_join(philo[index].thread_id, NULL);

	index = -1;
	while(++index < table->philos)
		pthread_mutex_destroy(&(table->forks[index]));
	pthread_mutex_destroy(&(table->log));
	pthread_mutex_destroy(&(table->m_death)); 
	// index = -1;
	// while(++index < table->philos)
	// 	pthread_detach(philo[index].thread_id);
}