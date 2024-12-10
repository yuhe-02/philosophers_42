/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/10 14:47:45 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//  TODO add validation
//  TODO check validation test
// 	TODO make sure if ac == 5 then continues until philosopher dies
int validate_params(t_params *params, int ac, char ** argv)
{
	// int is_not_num;

	// if (ac != 6)
	// 	return (1);
	// params->philos = ft_atoi(argv[1], &is_not_num);
	// params->ttd = ft_atoi(argv[2], &is_not_num);
	// params->tte = ft_atoi(argv[3], &is_not_num);
	// params->ttp = ft_atoi(argv[4], &is_not_num);
	// params->not = ft_atoi(argv[5], &is_not_num);
	// if (is_not_num)
	// 	return (1);
	params->philos = 5;
	params->ttd = 800;
	params->tte = 200;
	params->ttp = 200;
	params->not = 7;
}

void	start(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->philos)
	{
		if (pthread_create())
	}
}

void	show_params(t_params *params)
{
	YYAMASAK("philos                                   : %d\n", params->philos);
	YYAMASAK("time to die                              : %d sec\n", params->ttd);
	YYAMASAK("time to eat                              : %d sec\n", params->tte);
	YYAMASAK("time to sleep                            : %d\n", params->ttp);
	YYAMASAK("number of times each philosopher must eat: %d\n", params->not);
}

int main(int argc, char **argv)
{
	t_params	params;

	validate_params(&params, argc, argv);
	// show_params(&params);
}