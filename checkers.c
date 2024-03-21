/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:34:01 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/21 02:42:18 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_philo *philo)
{
	t_table	*table;
	int		index;

	philo = philo->table->philo;
	table = philo->table;
	index = -1;
	if (table->meals < 0)
		return (0);
	while(++index < table->philos)
	{
		if (philo[index].eated < table->meals)
				return (table->philo_down);
	}
	table->philo_down = 1;
	return (table->philo_down);
}

int check_death(t_philo *philo)
{
	long long	fasting;
	t_table		*table;
	int			index;

	table = philo->table;
	philo = table->philo;
	index = -1;
	while(++index < table->philos)
	{
	 	fasting = time_now() - philo->last_meal;
		if (fasting > philo[index].table->ttd)
		{
			philog(philo, DEAD);
			philo->table->philo_down = 1;
			break;
		}
	}
	return (philo->table->philo_down);
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
		pthread_detach(philo[index].thread_id),
		pthread_mutex_destroy(&(table->forks[index]));
	pthread_mutex_destroy(&(table->log));
	pthread_mutex_destroy(&(table->m_death)); 
}
