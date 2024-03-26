/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:44 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/23 18:31:23 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_w(char *str)
{
	printf("[-] %s\n", str);
	exit(1);
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
	sem_wait(philo->l_fork);
	philog(philo, FORK);
	if (table->philos == 1)
		return (smart_sleep(table->ttd, table), 1);
	sem_wait(philo->r_fork);
	philog(philo, FORK);
	philog(philo, EAT);
	philo->last_meal = time_now();
	if (!smart_sleep(philo->table->tte, philo->table))
		philo->eated++;
	sem_post(philo->r_fork);
	sem_post(philo->l_fork);
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
