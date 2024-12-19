/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_act.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:53:54 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:06:52 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_act(t_params *params, int id, char *str, int mode)
{
	long long	time_diff;
	int			dead_flag;
	int			err_flg;

	dead_flag = ft_dead_check(params, mode);
	pthread_mutex_lock(&(params->print_key));
	time_diff = ft_timeofday() - params->start_time;
	if (!dead_flag)
		printf("%lld %i %s\n", time_diff, id + 1, str);
	pthread_mutex_unlock(&(params->print_key));
	return (dead_flag);
}
