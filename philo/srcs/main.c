/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/19 16:08:36 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;

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
		return (prepare_for_die(&params));
	return (launch_thread(&params));
}
