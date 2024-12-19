/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:26:48 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:27:59 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_thread(t_params *params)
{
	int		i;
	t_philo	*philo;
	t_owner	*owner;

	i = 0;
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		philo->last_meal = ft_timeofday();
		pthread_create(&(philo->t_id), NULL, start_philo, (void *)philo);
		i++;
	}
	owner = &(params->owner);
	pthread_create(&(owner->t_id), NULL, start_owner, (void *)(owner));
	i = 0;
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		pthread_join(philo->t_id, NULL);
		i++;
	}
	pthread_join(owner->t_id, NULL);
	return (0);
}