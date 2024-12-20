/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/20 20:33:49 by yyamasak         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_params	params;
	int			flag;

	flag = 0;
	if (argc != 6 && argc != 5)
	{
		printf("input error. At least 4 parameters.\n");
		return (1);
	}
	if (validate_params(&params, argc, argv))
		return (1);
	init_philos(&params);
	init_owner(&params);
	if (init_forks(&params) == 1)
	{
		printf("Error: failed to initialize forks mutex\n");
		return (1);
	}
	params.start_time = ft_timeofday();
	if (params.nop == 1)
		flag = prepare_for_die(&params);
	else
		flag = launch_thread(&params);
	return (destroy_key(&params, params.nop, flag));
}
