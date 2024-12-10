/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:34:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/10 14:21:09 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>

#ifdef YYAMASAK_DEBUG
# define YYAMASAK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define YYAMASAK(fmt, ...)
#endif

typedef struct	s_params
{
	int philos;
	int ttd;
	int tte;
	int ttp;
	int not;
}				t_params;

// typedef struct	s_philo
// {
// 	int philos;
// 	int ttd;
// 	int tte;
// 	int ttp;
// 	int not;
// }				t_philo ;


// utils
int			ft_atoi(const char *str, int* is_not_num);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
#endif