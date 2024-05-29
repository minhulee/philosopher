/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:30:56 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/28 21:16:10 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	return ;
}

static int	is_digit_atoi(char *s)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			exit_err(INVALID_ARGV);
		sum *= 10;
		sum += *s - 48;
		s++;
	}
	if ((sign * sum) < 0 || INT_MAX < (sign * sum))
		exit_err(INVALID_ARGV);
	return (sum * sign);
}

void	parsing(t_pi *info, int ac, char **s)
{
	info->philo = is_digit_atoi(s[0]);
	info->dead = is_digit_atoi(s[1]);
	info->eat = is_digit_atoi(s[2]);
	info->sleep = is_digit_atoi(s[3]);
	if (ac == 6)
		info->must = is_digit_atoi(s[4]);
}
