/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:36:18 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/18 15:18:49 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//  TODO add validation
//  TODO check validation test
// 	TODO make sure if ac == 5 then continues until philosopher dies
int validate_params(t_params *params, int ac, char ** argv)
{
	int is_valid_num;

	is_valid_num = 0;
	if (ac != 6 && ac != 5)
		return (1);
	params->nop = ft_atoi_with_flg(argv[1], &is_valid_num);
	params->ttd = ft_atoi_with_flg(argv[2], &is_valid_num);
	params->tte = ft_atoi_with_flg(argv[3], &is_valid_num);
	params->tts = ft_atoi_with_flg(argv[4], &is_valid_num);
	if (ac == 5)
		params->not = -1;
	else
		params->not = ft_atoi_with_flg(argv[5], &is_valid_num);
	if (is_valid_num)
		return (1);
	params->finish_meal = 0;
	params->dead_flag = False;
	params->owner.params = params;
	return (0);
}
int	init_owner(t_params *params)
{
	params->owner.params = params;
	return (0);
}

int	init_philos(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nop)
	{
		params->philo[i].id = i;
		params->philo[i].last_meal = 0;
		params->philo[i].meal_times = 0;
		params->philo[i].dead_flag = False;
		params->philo[i].l_fork = i;
		params->philo[i].r_fork = i - 1;
		params->philo[i].params = params;
		// if (params->nop % 2 == 0)
		// {
		// 	if ((i + 1) % 2 == 0)
		// 		params->philo[i].first_sleep_time = params->tte;
		// 	else
		// 		params->philo[i].first_sleep_time = 0;
		// }
		// else 
		// {
		// 	if ((i + 1) % 2 == 0)
		// 		params->philo[i].first_sleep_time = ((2 * params->nop - 1) * params->tte) / (params->nop - 1);
		// 	else
		// 		params->philo[i].first_sleep_time = ((params->nop - 1) * params->tte) / (params->nop - 1);;
		// }
		if ((i + 1) % 2 == 0)
			params->philo[i].first_sleep_time = 15000;
		else
			params->philo[i].first_sleep_time = 0;
		if (i == 0)
		{
			params->philo[i].l_fork = i;
			params->philo[i].r_fork = params->nop - 1;
		}
		i++;
	}
	return (0);
}

int	init_forks(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nop)
	{
		pthread_mutex_init(&(params->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(params->print_key), NULL);
	pthread_mutex_init(&(params->dead_key), NULL);
	pthread_mutex_init(&(params->meal_key), NULL);
	return (0);
}