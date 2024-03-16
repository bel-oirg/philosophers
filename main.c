/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:23:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/16 05:29:21 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philo *philo)
{
	long long fasting;

	fasting = time_now() - philo->last_meal;
	if (fasting > philo->table->ttd)
		philo->table->philo_down = 1;
	return (philo->table->philo_down);
}

void	destroy_philo(t_philo *philo)
{
	t_table	*table;
	int		index;

	index = -1;
	table = philo->table;
	while(++index < table->philos)
		pthread_mutex_destroy(&(table->forks[index]));
	index = -1;
	while(++index < table->philos)
		pthread_detach(philo[index].thread_id);
	pthread_mutex_destroy(table->log);
}

int	check_full(t_philo *philo)
{
	int 	index;
	t_table	*table;

	if (philo->table->meals < 0)
		return (0);
	index = -1;
	table = philo->table;
	philo = philo->table->philo;
	while(++index < table->philos)
	{
		if (philo[index].eated < table->meals)
			break;
	}
	if (index == table->philos)
		return (1);
	return (0);
}

void	*monitor(void *philo_raw)
{
	t_philo *philo;

	philo = (t_philo *)philo_raw;
	while (1)
	{
		if (check_death(philo))
			return (philog(philo, DEAD), destroy_philo(philo), NULL);
		else if (check_full(philo))
		{
			pthread_mutex_lock((philo->table->log));
			destroy_philo(philo);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(philo->l_fork);
	philog(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	philog(philo, FORK);
	philo->last_meal = time_now();
	philog(philo, EAT);
	philo->eated++;
	smart_sleep(table->tte, table);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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

void	*begin(void *philo_raw)
{
	t_philo *philo;

	philo = (t_philo *) philo_raw;
	if (!(philo->id % 2))
		usleep(1500);
	while(1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	pthread_t monitor_th; 
	t_table	table;
	t_philo p[200];
	int		index;

	check_args(argc);
	parse_args(argc, argv, &table);
	init_philo(&table, p);
	index = -1;
	table.start = time_now();
	while(++index < table.philos)
	{
		p[index].last_meal = table.start;
		pthread_create(&(p[index].thread_id), NULL, begin, &(p[index]));
	}
	index = -1;
	while(++index < table.philos)
		pthread_join(p[index].thread_id, NULL);
	pthread_create(&monitor_th, NULL, monitor, &p);
	pthread_join(monitor_th, NULL);
}
