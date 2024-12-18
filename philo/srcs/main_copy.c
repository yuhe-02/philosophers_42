/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/18 12:16:52 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	sleep_overtime(long long time, t_params *params)
{
	long long start_to_sleep;

	start_to_sleep = timestamp();
	while (!params->dead_flag)
	{
		if (timestamp() - start_to_sleep >= time)
			break ;
		usleep(50);
	}
}

void	print_action(t_params *params, int id, char *str)
{
	long long time_diff;

	pthread_mutex_lock(&(params->print_key));
	time_diff = timestamp() - params->start_time;
	if (!(params->dead_flag))
		printf("%lld %i %s\n", time_diff, id + 1, str);
	pthread_mutex_unlock(&(params->print_key));
	return ;
}

void	ft_eat(t_philo *philo)
{
	t_params *params;

	params = philo->params;
	pthread_mutex_lock(&(params->forks[philo->l_fork]));
	print_action(params, philo->id, "has taken a fork");
	pthread_mutex_lock(&(params->forks[philo->r_fork]));
	print_action(params, philo->id, "has taken a fork");
	pthread_mutex_lock(&(params->meal_key));
	print_action(params, philo->id, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(params->meal_key));
	sleep_overtime(params->tte, params);
	// (philo->x_ate)++;
	pthread_mutex_unlock(&(params->forks[philo->l_fork]));
	pthread_mutex_unlock(&(params->forks[philo->r_fork]));
}

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
	params->nop = 10;
	params->ttd = 800;
	params->tte = 200;
	params->tts = 200;
	params->not = 7;
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
		params->philo[i].remain_times = params->not;
		params->philo[i].dead_flag = False;
		params->philo[i].l_fork = i;
		params->philo[i].r_fork = i - 1;
		params->philo[i].params = params;
		if (params->nop % 2 == 0)
		{
			if ((i + 1) % 2 == 0)
				params->philo[i].first_sleep_time = params->tte;
			else
				params->philo[i].first_sleep_time = 0;
		}
		else 
		{
			if ((i + 1) % 2 == 0)
				params->philo[i].first_sleep_time = ((2 * params->nop - 1) * params->tte) / (params->nop - 1);
			else
				params->philo[i].first_sleep_time = ((params->nop - 1) * params->tte) / (params->nop - 1);;
		}
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

void	*start(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)arg;
	params = philo->params;
	usleep(philo->first_sleep_time);
	while (!(params->dead_flag))
	{
		ft_eat(philo);
		// if (rules->all_ate)
		// 	break ;
		print_action(params, philo->id, "is sleeping");
		sleep_overtime(params->tts, params);
		// smart_sleep(rules->time_sleep, rules);
		print_action(params, philo->id, "is thinking");
		usleep(50);
			
		// smart_sleep(rules->time_sleep, rules);
		// action_print(rules, philo->id, "is thinking");
		// i++;
	}
	return (NULL);
}

void	*start_owner(void *arg)
{
	t_philo		*philo;
	t_owner		*owner;
	t_params	*params;
	int			i;

	owner = (t_owner *)arg;
	params = owner->params;
	philo = params->philo;
	i = 0;
	while (!(params->dead_flag))
	{
		i = -1;
		while (++i < params->nop)
		{
			pthread_mutex_lock(&(params->meal_key));
			if (params->ttd <= timestamp() - (params->start_time + philo[i].last_meal))
			{
				pthread_mutex_lock(&(params->dead_key));
				print_action(params, philo[i].id, "died");
				params->dead_flag = True;
				pthread_mutex_unlock(&(params->dead_key));
				pthread_mutex_unlock(&(params->meal_key));
				break ;
			}
			pthread_mutex_unlock(&(params->meal_key));
		}
		usleep(200);
	}
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
	params.start_time = timestamp();
	while (i < params.nop)
	{
		philo = &(params.philo[i]);
		pthread_create(&(philo->t_id), NULL, start, philo);
		i++;
	}
	pthread_create(&(params.owner.t_id), NULL, start_owner, &(params.owner));
	i = 0;
	while (i < params.nop)
	{
		philo = &(params.philo[i]);
		pthread_join(philo->t_id, NULL);
		i++;
	}
	pthread_join(params.owner.t_id, NULL);
	// show_philos(&params);
	// show_params(&params);
	return (0);
}