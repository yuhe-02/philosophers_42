/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:26:48 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/20 20:37:42 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	detach_thread(t_params *params, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		pthread_detach(params->philo[i].t_id);
		i++;
	}
	if (i == params->nop)
		pthread_detach(params->owner.t_id);
	printf("failed to create thread\n");
	return (1);
}

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
	int		flag;

	i = 0;
	flag = 0;
	owner = &(params->owner);
	while (i < params->nop)
	{
		philo = &(params->philo[i]);
		if (pthread_create(&(philo->t_id), NULL, start_philo, (void *)philo))
		{
			flag = detach_thread(params, i);
			break ;
		}
		philo->last_meal = ft_timeofday();
		i++;
	}
	if (flag == 0
		&& pthread_create(&(owner->t_id), NULL, start_owner, (void *)(owner)))
		flag = detach_thread(params, i);
	if (flag == 0)
		all_join_thread(params);
	return (flag);
}
