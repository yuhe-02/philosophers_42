/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:18:39 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/18 12:36:16 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_if_dead(t_params *params)
{
	pthread_mutex_lock(&(params->dead_key));
	if (params->dead_flag)
	{
		pthread_mutex_unlock(&(params->dead_key));
		return (1);
	}
	pthread_mutex_unlock(&(params->dead_key)); 
	return (0);
}

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
	while (!(check_if_dead(params)))
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
	if (!(check_if_dead(params)))
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

void	*start(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)arg;
	params = philo->params;
	usleep(philo->first_sleep_time);
	while (!(check_if_dead(params)))
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