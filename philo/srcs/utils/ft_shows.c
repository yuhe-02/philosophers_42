/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shows.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:01:45 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/16 14:45:01 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_params(t_params *params)
{
	YYAMASAK("philos                                   : %d\n", params->nop);
	YYAMASAK("time to die                              : %d sec\n", params->ttd);
	YYAMASAK("time to eat                              : %d sec\n", params->tte);
	YYAMASAK("time to sleep                            : %d\n", params->tts);
	YYAMASAK("number of times each philosopher must eat: %d\n", params->not);
}

void	show_philos(t_params *params)
{
	int		i;
	t_philo	philo;

	i = 0;
	while (i < params->nop)
	{
		philo = params->philo[i];
		YYAMASAK("\n");
		YYAMASAK("id: %d\n", philo.id);
		YYAMASAK("t_id: %lu\n", (unsigned long)philo.t_id);
		YYAMASAK("r_fork: %d\n", philo.r_fork);
		YYAMASAK("l_fork: %d\n", philo.l_fork);
		YYAMASAK("last_meal: %lld\n", philo.last_meal);
		YYAMASAK("remain_times: %d\n", philo.remain_times);
		YYAMASAK("dead_flag: %d\n", philo.dead_flag);
		YYAMASAK("--------------------------\n");
		YYAMASAK("\n");
		i++;
	}
}