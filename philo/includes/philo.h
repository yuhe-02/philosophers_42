/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:34:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/18 12:06:03 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>

#ifdef YYAMASAK_DEBUG
# define YYAMASAK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define YYAMASAK(fmt, ...)
#endif


typedef enum s_bool 
{
	False = 0,
	True = 20
}	t_bool ;

/*
param
	id: philosopher number(start with 0)
	t_id: thread id
	r_fork: right side fork number(start with 0)
	l_fork: left side fork number(start with 0)
	last_meal: last meal time(initialized as 0)
	remain_times: the number of meals remaining with philosopher(if remain time is infinite, defined as -1)
	dead_flag: the status of whether if he/she is living
*/
typedef struct	s_philo
{
	int					id;
	pthread_t			t_id;
	int					r_fork;
	int					l_fork;
	long long			last_meal;
	int					remain_times;
	t_bool				dead_flag;
	int					first_sleep_time;
	struct s_params		*params;
}				t_philo ;

typedef struct	s_owner
{
	struct s_params		*params;
	pthread_t			t_id;
}				t_owner ;

/*
param
	nop: number of philosophers
	ttd: time to die
	tte: time to eat
	tts: time to sleep
	not: number_of_times_each_philosopher_must_eat(if infinite, defined as -1)
	forks[]: mutex key
	philo[]: philosophers
*/
typedef struct	s_params
{
	int					nop;
	int					ttd;
	int					tte;
	int					tts;
	int					not;
	long long			start_time;
	t_bool				dead_flag;
	t_owner				owner;
	pthread_mutex_t		dead_key;
	pthread_mutex_t		meal_key;
	pthread_mutex_t		print_key;
	pthread_mutex_t		forks[200];
	t_philo				philo[200];
}				t_params;



// utils
int			ft_atoi(const char *str, int* is_not_num);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// show
void	show_params(t_params *params);
void	show_philos(t_params *params);
#endif