/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/16 15:39:33 by yyamasak         ###   ########.fr       */
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
	params->nop = 5;
	params->ttd = 800;
	params->tte = 200;
	params->tts = 200;
	params->not = 7;
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
		params->philo[i].remain_times = params->not;
		params->philo[i].dead_flag = False;
		params->philo[i].l_fork = i;
		params->philo[i].r_fork = i - 1;
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
	return (0);
}

void	*start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	YYAMASAK("number: %d, time: %ld\n", philo->id, philo->t_id);
	return (NULL);
}


// TODO create logic(lock)
int main(int argc, char **argv)
{
	t_params	params;
	int			i;
	t_philo		*philo;

	i = 0;
	validate_params(&params, argc, argv);
	init_philos(&params);
	init_forks(&params);
	while (i <= params.nop)
	{
		philo = &(params.philo[i]);
		pthread_create(&(philo->t_id), NULL, start, philo);
		i++;
	}
	show_philos(&params);
	// show_params(&params);
}