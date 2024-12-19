/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owner_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:21:16 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:24:16 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	_ft_death_check(t_params *params, t_philo *philo, int i)
{
	pthread_mutex_lock(&(params->meal_keys[i]));
	if (params->ttd <= ft_timeofday() - philo->last_meal)
	{
		pthread_mutex_lock(&(params->dead_key));
		ft_print_act(params, philo->id, "died", 1);
		params->dead_flag = 1;
		pthread_mutex_unlock(&(params->dead_key));
		pthread_mutex_unlock(&(params->meal_keys[i]));
		return (1);
	}
	pthread_mutex_unlock(&(params->meal_keys[i]));
	return (0);
}

static int	_ft_check_finished(t_params *params)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = params->philo;
	while (params->not != -1 && i < params->nop)
	{
		if (philo[i].meal_times < params->not)
			return (0);
		i++;
	}
	return (1);
}

void	*start_owner(void *arg)
{
	t_philo		*philo;
	t_params	*params;
	int			i;

	params = ((t_owner *)arg)->params;
	philo = params->philo;
	while (!params->finish_meal)
	{
		i = -1;
		while (++i < params->nop && !(params->dead_flag))
		{
			if (!philo[i].last_meal)
				continue ;
			if (_ft_death_check(params, &(philo[i]), i) == 1)
				break ;
			usleep(50);
		}
		if (params->dead_flag)
			break ;
		if (params->not != -1 && _ft_check_finished(params) == 1)
			params->finish_meal = 1;
	}
	return (NULL);
}