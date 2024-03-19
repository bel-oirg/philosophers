/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:56:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/18 05:15:51 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define FORK	"has taken a fork"
#define SLEEP	"is sleeping"
#define THINK	"is thinking"
#define EAT		"is eating"
#define DEAD	"died"

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_table	*table;
	long long		last_meal;
	pthread_t		thread_id;
	int				eated;
	int				id;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	forks[200];
	pthread_mutex_t	m_death;
	pthread_mutex_t m_meals;
	pthread_mutex_t	log;
	t_philo			*philo;
	long long		start;
	long long		ttd;
	long long		tte;
	long long		tts;
	long			meals;
	long			philos;
	int				philo_down;
	int				full;
}	t_table;

//philo_utils
int			smart_sleep(long interval, t_table *table);
void		philog(t_philo *philo, const char *action);
long long	time_now(void);

//utils
void		err_w(char *str);
int			check_args(int argc);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

//parse_init
long		ft_atol(char *str);
int			init_philo(t_table *table, t_philo *p);
int			parse_args(char *argv[], t_table *table);

//checkers.c
int			check_full(t_philo *philo);
int			check_death(t_philo *philo);
void		destroy_philo(t_table *table);