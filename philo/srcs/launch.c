/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:26:48 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 19:57:07 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	destroy_key(t_params *params, int end, int ret)
{
	int	i;

	i = 0;
	while (i < end)
	{
		pthread_mutex_destroy(&(params->forks[i]));
		pthread_mutex_destroy(&(params->meal_keys[i]));
		i++;
	}
	pthread_mutex_destroy(&(params->print_key));
	pthread_mutex_destroy(&(params->dead_key));
	return (ret);
}

// static	int destroy_all(t_params *params, int end)
// {
// 	int	i;

// 	i = 0;
// 	while (i < end)
// 	{
// 		pthread_detach(params->philo[i].t_id); 
// 		i++;
// 	}
// 	if (i == params->nop)
// 		pthread_detach(params->owner.t_id);
// 	destroy_key(params, i);
// 	return (1);
// }

static int	all_join_thread(t_params *params)
{
	int		i;
	t_philo	*philo;
	t_owner	*owner;

	i = 0;
	owner = &(params->owner);
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		pthread_join(philo->t_id, NULL);
		i++;
	}
	pthread_join(owner->t_id, NULL);
	return (0);
}

int	launch_thread(t_params *params)
{
	int		i;
	t_philo	*philo;
	t_owner	*owner;

	i = 0;
	owner = &(params->owner);
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		if (pthread_create(&(philo->t_id), NULL, start_philo, (void *)philo))
			return (destroy_key(params, params->nop, 1));
		philo->last_meal = ft_timeofday();
		i++;
	}
	if (pthread_create(&(owner->t_id), NULL, start_owner, (void *)(owner)))
		return (destroy_key(params, params->nop, 1));
	all_join_thread(params);
	return (destroy_key(params, params->nop, 0));
}