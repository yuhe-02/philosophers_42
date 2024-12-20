/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:34:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/20 15:31:20 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		t_id;
	int				r_fork;
	int				l_fork;
	long long		last_meal;
	int				meal_times;
	int				dead_flag;
	int				first_sleep_time;
	struct s_params	*params;

}					t_philo;

typedef struct s_owner
{
	struct s_params	*params;
	pthread_t		t_id;
	int				meal_times[200];
}					t_owner;

typedef struct s_params
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				not;
	int				finish_meal;
	long long		start_time;
	int				dead_flag;
	t_owner			owner;
	pthread_mutex_t	dead_key;
	pthread_mutex_t	print_key;
	pthread_mutex_t	meal_keys[200];
	pthread_mutex_t	forks[200];
	t_philo			philo[200];
}					t_params;

int					validate_params(t_params *params, int ac, char **argv);
int					init_owner(t_params *params);
int					init_philos(t_params *params);
int					init_forks(t_params *params);
int					prepare_for_die(t_params *params);
int					launch_thread(t_params *params);
void				*start_owner(void *arg);
void				*start_philo(void *arg);
int					ft_atoi_with_flg(const char *str, int *is_not_num);
long long			ft_timeofday(void);
int					ft_dead_check(t_params *params, int mode);
int					ft_print_act(t_params *params, int id, char *str, int mode);
int					ft_print_act2(t_params *params, int id, char *str);

#endif