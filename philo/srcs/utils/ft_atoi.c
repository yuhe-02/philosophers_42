/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:52:33 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/10 14:03:21 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	minus_skip(const char *str, int *i, int *minus)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*minus = -1;
		(*i)++;
	}
}

int	trim_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	is_limit_value(long *digits, int value, int *minus)
{
	int	flg;

	flg = 0;
	if (*minus == -1)
	{
		if (-*digits < (LONG_MIN + value) / 10)
		{
			*digits = LONG_MIN;
			flg = 1;
			*minus = 1;
		}
	}
	else
	{
		if (*digits > (LONG_MAX - value) / 10)
		{
			flg = 1;
			*digits = LONG_MAX;
		}
	}
	return (flg);
}

int	ft_atoi(const char *str, int* is_not_num)
{
	long	digits;
	int		i;
	int		minus;

	minus = 1;
	digits = 0;
	i = trim_space(str);
	minus_skip(str, &i, &minus);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (is_limit_value(&digits, str[i] - '0', &minus))
			break ;
		digits = digits * 10 + (str[i] - '0');
		i++;
	}
	if (i == 0 || str[i] != '\0')
		*is_not_num = 1;
	digits *= minus;
	return ((int)digits);
}