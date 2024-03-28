/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:40:44 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/27 19:39:31 by bel-oirg         ###   ########.fr       */
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

void	ft_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (sem_wait(philo->l_fork))
		err_w("Failed to wait a semaphore");
	philog(philo, FORK);
	if (table->philos == 1)
		return (smart_sleep(table->ttd, table));
	if (sem_wait(philo->r_fork))
		err_w("Failed to wait a semaphore");
	philog(philo, FORK);
	philog(philo, EAT);
	philo->last_meal = time_now();
	smart_sleep(philo->table->tte, philo->table);
	philo->eated++;
	if (sem_post(philo->r_fork))
		err_w("Sem post failed");
	if (sem_post(philo->l_fork))
		err_w("Sem post failed");
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
