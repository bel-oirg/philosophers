/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:56:19 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/03/13 06:20:41 by bel-oirg         ###   ########.fr       */
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
	int				id;
	int				eated;
	long long		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_table	*table;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	forks[200];
	int				philo_down;
	long long		start;
	long			philos;
	long			meals;
	long long		ttd;
	long long		tte;
	long long		tts;
	t_philo			*philo;
}	t_table;


//philo_utils
// int			none_dead(t_table *table);
void		smart_sleep(long interval, t_table *table);
void		philog(long long start, int id, const char *action);
long long	time_now(void);

//utils
void	err_w(char *str);
int		abs_v(int num);
void	check_args(int argc);
long	ft_atol(char *str);