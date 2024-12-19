/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dead_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:56:07 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 19:35:44 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead_check(t_params *params, int mode)
{
	int	dead_flag;

	if (mode == 0)
	{
		pthread_mutex_lock(&(params->dead_key));
		dead_flag = params->dead_flag;
		pthread_mutex_unlock(&(params->dead_key));
		return (dead_flag);
	}
	return (params->dead_flag);
}
