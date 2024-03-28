/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:56:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/28 03:46:37 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <semaphore.h>

#define FORK	"has taken a fork"
#define SLEEP	"is sleeping"
#define THINK	"is thinking"
#define EAT		"is eating"
#define DEAD	"died"

typedef struct s_philo
{
	struct s_table		*table;
	_Atomic long long	last_meal;
	sem_t				*l_fork;
	sem_t				*r_fork;
	pid_t				pid_id;
	int					eated;
	int					id;
}	t_philo;

typedef struct s_table
{
	sem_t			*forks;
	sem_t			*log;
	sem_t			*the_end;
	long long		start;
	long long		ttd;
	long long		tte;
	long long		tts;
	t_philo			*philo;
	long			meals;
	long			philos;
	int				philo_down;
}	t_table;

//philo_utils
void		smart_sleep(long interval, t_table *table);
void		philog(t_philo *philo, const char *action);
void		begin(t_philo *philo);
long		ft_atol(char *str);

//utils
long long	time_now(void);
void		err_w(char *str);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
