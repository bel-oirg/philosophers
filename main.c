/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:23:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/28 03:51:07 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_args(char *argv[], t_table *table)
{
	table->philos = ft_atol(argv[1]);
	table->ttd = ft_atol(argv[2]);
	table->tte = ft_atol(argv[3]);
	table->tts = ft_atol(argv[4]);
	table->meals = -1;
	if (argv[5])
		table->meals = ft_atol(argv[5]);
	if (table->philos > 200)
		err_w("We have only 200 chairs");
}

static void	init_philo(t_table *table, t_philo *p)
{
	int		index;

	sem_unlink("sem_log");
	sem_unlink("sem_forks");
	sem_unlink("sem_the_end");
	table->forks = sem_open("sem_forks", O_CREAT, 0644, table->philos);
	if (table->forks == SEM_FAILED)
		err_w("Failed to open semaphore - forks");
	table->log = sem_open("sem_log", O_CREAT, 0644, 1);
	if (table->log == SEM_FAILED)
		err_w("Failed to open semaphore - log");
	table->the_end = sem_open("sem_the_end", O_CREAT, 0644, 0);
	if (table->the_end == SEM_FAILED)
		err_w("Failed to open semaphore - the_end");
	index = table->philos;
	while (--index >= 0)
	{
		p[index].table = table;
		p[index].eated = 0;
		p[index].id = index + 1;
	}
	table->philo_down = 0;
	table->philo = p;
}

static void	nietzsche_party(t_table *table)
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
		(forked < 0) && (err_w("Failed to fork - forked"), 0);
		(!forked) && (begin(philo + index), 0);
		(forked > 0) && (philo[index].pid_id = forked);
	}
	index = -1;
	while (++index < table->philos)
		if (sem_wait(table->the_end))
			err_w("Failed to wait a semaphore - the_end");
}

static void	destroy_philo(t_table *table)
{
	t_philo	*philo;
	int		index;

	philo = table->philo;
	index = -1;
	while (++index < table->philos)
		kill(table->philo[index].pid_id, SIGKILL);
	sem_close(table->log);
	sem_close(table->forks);
	sem_close(table->the_end);
	sem_unlink("sem_log");
	sem_unlink("sem_forks");
	sem_unlink("sem_the_end");
}

int	main(int argc, char *argv[])
{
	t_table		table;
	t_philo		p[200];

	if (argc != 5 && argc != 6)
		err_w("Invalid number of args");
	parse_args(argv, &table);
	init_philo(&table, p);
	nietzsche_party(&table);
	destroy_philo(&table);
}
