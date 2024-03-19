/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:44 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/19 04:43:52 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_w(char *str)
{
	printf("[-] %s\n", str);
}

int	check_args(int argc)
{
	if (argc != 5 && argc != 6)
		return (err_w("Invalid number of args"), 1);
	return (0);
}

int		ft_eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;

	pthread_mutex_lock(philo->l_fork);
	philog(philo, FORK);

	pthread_mutex_lock(philo->r_fork);
	philog(philo, FORK);

	philog(philo, EAT);
	philo->last_meal = time_now();
	if (!smart_sleep(philo->table->tte, philo->table))
	{
		// pthread_mutex_lock(&(table->m_meals));
		philo->eated++;
		if (check_full(philo))
			pthread_mutex_lock(&(table->log));
		// pthread_mutex_unlock(&(table->m_meals));
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (table->full || table->philo_down)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	philog(philo, SLEEP);
	return (smart_sleep(philo->table->tts, philo->table));
}

void	ft_think(t_philo *philo)
{
	philog(philo, THINK);
}
