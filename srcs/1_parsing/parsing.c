/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:30:56 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/31 16:17:33 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	info->philo_num = is_digit_atoi(s[0]);
	info->die_to_time = is_digit_atoi(s[1]);
	info->eat_to_time = is_digit_atoi(s[2]);
	info->sleep_to_time = is_digit_atoi(s[3]);
	if (ac == 6)
		info->must_eat = is_digit_atoi(s[4]);
}
