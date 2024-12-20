/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owner_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:21:16 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/20 15:49:07 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_ft_death_check(t_params *params, t_philo *philo, int i)
{
	long long	elapsed_time_after_meal;

	pthread_mutex_lock(&(params->meal_keys[i]));
	params->owner.meal_times[i] = philo->meal_times;
	elapsed_time_after_meal = ft_timeofday() - philo->last_meal;
	pthread_mutex_unlock(&(params->meal_keys[i]));
	if (params->ttd < elapsed_time_after_meal)
	{
		pthread_mutex_lock(&(params->dead_key));
		params->dead_flag = 1;
		pthread_mutex_unlock(&(params->dead_key));
		ft_print_act2(params, philo->id, "died");
		return (1);
	}
	return (0);
}

static int	_ft_check_finished(t_params *params)
{
	int		i;

	i = 0;
	while (params->not != -1 && i < params->nop)
	{
		if (params->owner.meal_times[i] < params->not)
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
