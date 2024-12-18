/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/18 15:16:57 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_if_dead(t_params *params, int mode)
{
	int dead_flag;

	if (mode == 0)
	{
		pthread_mutex_lock(&(params->dead_key));
		dead_flag = params->dead_flag;
		pthread_mutex_unlock(&(params->dead_key));
		return (dead_flag);
	}
	return (params->dead_flag);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	sleep_overtime(long long time, t_params *params)
{
	long long start_to_sleep;

	start_to_sleep = timestamp();
	while (!(check_if_dead(params, 0)))
	{
		if (timestamp() - start_to_sleep >= time)
			break ;
		usleep(50);
	}
}

void	print_action(t_params *params, int id, char *str, int mode)
{
	long long time_diff;
	int			dead_flag;

	dead_flag = check_if_dead(params, mode);
	pthread_mutex_lock(&(params->print_key));
	time_diff = timestamp() - params->start_time;
	if (!dead_flag)
		printf("%lld %i %s\n", time_diff, id + 1, str);
	pthread_mutex_unlock(&(params->print_key));
	return ;
}

void	ft_eat(t_philo *philo)
{
	t_params *params;

	params = philo->params;
	pthread_mutex_lock(&(params->forks[philo->l_fork]));
	print_action(params, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(params->forks[philo->r_fork]));
	print_action(params, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(params->meal_key));
	print_action(params, philo->id, "is eating", 0);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(params->meal_key));
	sleep_overtime(params->tte, params);
	(philo->meal_times)++;
	pthread_mutex_unlock(&(params->forks[philo->l_fork]));
	pthread_mutex_unlock(&(params->forks[philo->r_fork]));
}

void	*start(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)arg;
	params = philo->params;
	philo->last_meal = timestamp();
	if (philo->l_fork == philo->r_fork)
		return (NULL);
	usleep(philo->first_sleep_time);
	while (!(check_if_dead(params, 0)))
	{
		ft_eat(philo);
		if (params->finish_meal)
			break ;
		print_action(params, philo->id, "is sleeping", 0);
		sleep_overtime(params->tts, params);
		print_action(params, philo->id, "is thinking", 0);
		usleep(50);
	}
	return (NULL);
}

void	*start_owner(void *arg)
{
	t_philo		*philo;
	t_owner		*owner;
	t_params	*params;
	int			i;
	int			meal_times;

	owner = (t_owner *)arg;
	params = owner->params;
	philo = params->philo;
	i = 0;
	while (!params->finish_meal)
	{
		i = -1;
		while (++i < params->nop && !(params->dead_flag))
		{
			if (!philo[i].last_meal)
				continue ;
			pthread_mutex_lock(&(params->meal_key));
			if (params->ttd <= timestamp() - philo[i].last_meal)
			{
				pthread_mutex_lock(&(params->dead_key));
				print_action(params, philo[i].id, "died", 1);
				params->dead_flag = True;
				pthread_mutex_unlock(&(params->dead_key));
				pthread_mutex_unlock(&(params->meal_key));
				break ;
			}
			pthread_mutex_unlock(&(params->meal_key));
		}
		if (params->dead_flag)
			break ;
		i = 0;
		while (params->not != -1 && i < params->nop)
		{
			meal_times = philo[i].meal_times;
			if (meal_times < params->not)
				break ;
			i++;
		}
		if (i == params->nop)
		{
			params->finish_meal = 1;
		}
		usleep(200);
	}
	return (NULL);
}


// TODO create logic(lock)
int main(int argc, char **argv)
{
	t_params	params;
	int			i;
	t_philo		*philo;

	i = 0;
	if (validate_params(&params, argc, argv))
		return (1);
	init_philos(&params);
	init_forks(&params);
	params.start_time = timestamp();
	while (i < params.nop)
	{
		philo = &(params.philo[i]);
		pthread_create(&(philo->t_id), NULL, start, philo);
		i++;
	}
	start_owner(&(params.owner));
	// pthread_create(&(params.owner.t_id), NULL, start_owner, &(params.owner));
	i = 0;
	while (i < params.nop)
	{
		philo = &(params.philo[i]);
		pthread_join(philo->t_id, NULL);
		i++;
	}
	// pthread_join(params.owner.t_id, NULL);
	return (0);
}