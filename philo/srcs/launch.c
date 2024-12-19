/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:26:48 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 19:14:22 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		pthread_create(&(philo->t_id), NULL, start_philo, (void *)philo);
		philo->last_meal = ft_timeofday();
		i++;
	}
	owner = &(params->owner);
	pthread_create(&(owner->t_id), NULL, start_owner, (void *)(owner));
	i = 0;
	all_join_thread(params);
	return (0);
}