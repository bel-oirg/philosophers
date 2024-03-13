/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:23:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/13 06:20:32 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(int argc, char *argv[], t_table *table)
{
	table->philos = ft_atol(argv[1]);
	table->ttd = ft_atol(argv[2]);
	table->tte = ft_atol(argv[3]);
	table->tts = ft_atol(argv[4]);
	table->meals = -1;
	if (argc == 6)
		table->meals = ft_atol(argv[5]);
	if (table->philos > 200)
		err_w("We have only 200 chairs");
	if (table->ttd < 60 || table->tte < 60 || table->tts < 60)
		err_w("Enter higher values");
}

void	init_philo(t_table *table, t_philo *p)
{
	long	philos;
	int		index;
	
	philos = table->philos;
	table->philo_down = 0;
	index = -1;
	while(++index < philos)
		pthread_mutex_init(&(table->forks[index]), NULL);
	index = -1;
	while (++index < philos)
	{
		p[index].table = table;
		p[index].eated = 0;
		p[index].id = index + 1;
		(p + index)->r_fork = &(table->forks[index]);
		(p + index)->l_fork = &(table->forks[abs_v(index - 1) % philos]);
	}
	table->philo = p;
}

void	ft_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->r_fork);
	philog(table->start, philo->id, FORK);
	pthread_mutex_lock(philo->l_fork);
	philog(table->start, philo->id, FORK);
	philo->last_meal = time_now();
	philog(table->start, philo->id, EAT);
	philo->eated++;
	smart_sleep(table->tte, table);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleep(t_philo *philo)
{
	philog(philo->table->start, philo->id, SLEEP);
	smart_sleep(philo->table->tts, philo->table);
}

void	ft_think(t_philo *philo)
{
	philog(philo->table->start, philo->id, THINK);
}


int check_death(t_philo *philo)
{
	long long fasting;

	fasting = time_now() - philo->last_meal;
	if (fasting >= philo->table->ttd)
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
	exit(1);
}

int	check_full(t_philo *philo)
{
	int 	index;
	t_table	*table;

	index = 0;
	table = philo->table;
	while(index < table->philos)
		if (philo[index].eated == philo->table->meals)
			index++;
	if (index == table->philos)
		return (1);
	return (0);
}

void	*begin(void *philo_raw)
{
	t_philo *philo;

	philo = (t_philo *) philo_raw;
	if (!(philo->id % 2))
		usleep(15000);
	while(1)
	{
		if (check_death(philo))
		{
			philog(philo->table->start, philo->id, DEAD);
			destroy_philo(philo);
		}
		if (philo->id == philo->table->philos - 1 && check_full(philo->table->philo))
			destroy_philo(philo);
		ft_eat(philo, philo->table);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
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
}
