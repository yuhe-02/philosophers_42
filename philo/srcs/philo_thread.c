/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:08:22 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:30:14 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_ft_sleep(long long time, t_params *params)
{
	long long	start_to_sleep;

	start_to_sleep = ft_timeofday();
	while (!(ft_dead_check(params, 0)))
	{
		if (ft_timeofday() - start_to_sleep >= time)
			break ;
		usleep(50);
	}
}

static int	_ft_eat(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	pthread_mutex_lock(&(params->forks[philo->l_fork]));
	if (ft_print_act(params, philo->id, "has taken a fork", 0) == 1)
	{
		pthread_mutex_unlock(&(params->forks[philo->l_fork]));
		return (1);
	}
	pthread_mutex_lock(&(params->forks[philo->r_fork]));
	if (ft_print_act(params, philo->id, "has taken a fork", 0) == 1)
	{
		pthread_mutex_unlock(&(params->forks[philo->l_fork]));
		pthread_mutex_unlock(&(params->forks[philo->r_fork]));
		return (1);
	}
	pthread_mutex_lock(&(params->meal_keys[philo->id]));
	ft_print_act(params, philo->id, "is eating", 0);
	philo->last_meal = ft_timeofday();
	(philo->meal_times)++;
	pthread_mutex_unlock(&(params->meal_keys[philo->id]));
	_ft_sleep(params->tte, params);
	pthread_mutex_unlock(&(params->forks[philo->l_fork]));
	pthread_mutex_unlock(&(params->forks[philo->r_fork]));
}

void	*start_philo(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)arg;
	params = philo->params;
	usleep(philo->first_sleep_time);
	while (1)
	{
		if (_ft_eat(philo) == 1)
			break ;
		if (params->finish_meal)
			break ;
		if (ft_print_act(params, philo->id, "is sleeping", 0) == 1)
			break ;
		_ft_sleep(params->tts, params);
		if (ft_print_act(params, philo->id, "is thinking", 0) == 1)
			break ;
		usleep(50);
	}
	return (NULL);
}
