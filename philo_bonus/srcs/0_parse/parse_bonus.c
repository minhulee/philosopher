/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:30:56 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:50:00 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	convert_sign(char **s, int *sign)
{
	if (*(*s) == '-' || *(*s) == '+')
	{
		if (*(*s) == '-')
			(*sign) *= -1;
		(*s)++;
	}
}

static int	is_digit_atoi(char *s)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	convert_sign(&s, &sign);
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			ft_err(INVALID_ARGV, NULL);
		sum *= 10;
		sum += *s - 48;
		s++;
	}
	if ((sign * sum) <= 0 || INT_MAX < (sign * sum))
		ft_err(INVALID_ARGV, NULL);
	return (sum * sign);
}

void	parsing(t_p_info *info, int ac, char **s)
{
	info->philo_num = is_digit_atoi(s[0]);
	info->time_to_die = is_digit_atoi(s[1]);
	info->time_to_eat = is_digit_atoi(s[2]);
	info->time_to_sleep = is_digit_atoi(s[3]);
	if (ac == 6)
		info->must_to_eat = is_digit_atoi(s[4]);
	else
		info->must_to_eat = -1;
}
