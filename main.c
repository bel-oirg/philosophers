/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:23:16 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/27 21:09:00 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_death(void *philo_raw)
{
	long long	fasting;
	t_table		*table;
	t_philo		*philo;
	int			index;

	philo = (t_philo *)philo_raw;
	table = philo->table;
	while (1)
	{
		fasting = time_now() - philo->last_meal;
		if (fasting > table->ttd)
		{
			philog(philo, DEAD);
			index = -1;
			while (++index < table->philos)
				if (sem_post(philo->table->the_end) == -1)
					err_w("Sem post failed");
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

static void	begin(t_philo *philo)
{
	pthread_t	monitor_th;
	t_table		*table;

	table = philo->table;
	philo->last_meal = time_now();
	if (pthread_create(&monitor_th, NULL, check_death, philo))
		err_w("Failed to create a thread");
	if (pthread_detach(monitor_th))
		err_w("Failed to detach a thread");
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		ft_eat(philo);
		if (philo->eated == table->meals)
		{
			if (sem_post(table->the_end) == -1)
				err_w("Sem post failed");
			exit(0);
		}
		ft_sleep(philo);
		ft_think(philo);
	}
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
		if (!forked)
			begin(philo + index);
		else
			philo[index].pid_id = forked;
	}
	index = -1;
	while (++index < table->philos)
		if (sem_wait(table->the_end))
			err_w("Failed to wait a semaphore");
}

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
	if (table->ttd < 60 || table->tte < 60 || table->tts < 60)
		err_w("Enter higher values");
}

int	main(int argc, char *argv[])
{
	t_table		table;
	t_philo		p[200];

	check_args(argc);
	parse_args(argv, &table);
	init_philo(&table, p);
	nietzsche_party(&table);
	destroy_philo(&table);
}
