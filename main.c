/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:23:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/25 19:52:15 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*supervisor(void *philo_raw)
{
	t_philo *philo;
	t_table	*table;

	philo = (t_philo *)philo_raw;
	table = philo->table;
	while (!table->philo_down)
	{
		usleep(100);
		check_death(philo);
		check_full(philo);
	}
	return (sem_post(table->the_end), NULL);
}

static void	*begin(void *philo_raw)
{
	pthread_t	monitor_th;
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *) philo_raw;
	table = philo->table;
	philo->last_meal = time_now();

	pthread_create(&monitor_th, NULL, supervisor, philo);
	pthread_detach(monitor_th);
	if (philo->id % 2)
		usleep(15000);
	while(!table->philo_down)
	{
		ft_eat(philo);
		if (philo->eated == table->meals)
			break;
		ft_sleep(philo);
		ft_think(philo);
	}
	return (exit(0), NULL);
}

static int	nietzsche_party(t_table *table)
{
	t_philo		*philo;
	int			index;
	int			forked;
	
	index = -1;
	table->start = time_now();
	philo = table->philo;
	while (++index < table->philos)
	{
		forked = fork();
		if (!forked)
			begin(philo + index);
		else
			philo[index].pid_id = forked;
	}
	sem_wait(table->the_end);
	destroy_philo(table);
	return (0);
}

int main(int argc, char *argv[])
{
	t_table		table;
	t_philo		p[200];

	if (check_args(argc))
		return (1);
	if (parse_args(argv, &table))
		return (1);
	if (init_philo(&table, p))
		return (1);
	if (nietzsche_party(&table))
		return (1);
}
