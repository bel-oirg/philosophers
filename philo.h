/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:56:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/16 02:05:44 by bel-oirg         ###   ########.fr       */
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
	pthread_mutex_t	*log;
	t_philo			*philo;
	long long		start;
	long long		ttd;
	long long		tte;
	long long		tts;
	long			meals;
	long			philos;
	int				philo_down;
}	t_table;

//philo_utils
void		smart_sleep(long interval, t_table *table);
void		philog(t_philo *philo, const char *action);
long long	time_now(void);

//utils
void	err_w(char *str);
int		abs_v(int num);
void	check_args(int argc);

//parse_init
long	ft_atol(char *str);
void	init_philo(t_table *table, t_philo *p);
void	parse_args(int argc, char *argv[], t_table *table);
