/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_die.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:43:14 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:22:13 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait_for_die(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal = ft_timeofday();
	while (1)
	{
		if (ft_timeofday() - philo->last_meal > philo->params->ttd)
		{
			ft_print_act(philo->params, philo->id, "died", 1);
			break ;
		}
		usleep(50);
	}
}

int	prepare_for_die(t_params *params)
{
	t_philo	*philo;

	philo = &(params->philo[0]);
	if (pthread_create(&(philo->t_id), NULL, wait_for_die, (void *)philo))
	{
		printf("failed to create thread\n");
		return (1);
	}
	pthread_join(philo->t_id, NULL);
	return (0);
}
