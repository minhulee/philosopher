/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:30:56 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/30 03:12:03 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	convert_sign(char **s, int *sign)
{
	if (*(*s) == '-' || *(*s) == '+')
	{
		if (*(*s) == '-')
			(*sign) *= -1;
		(*s)++;
	}
}

static t_b	is_digit_atoi(char *s, int *dest)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	convert_sign(&s, &sign);
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (FALSE);
		sum *= 10;
		sum += *s - 48;
		s++;
	}
	if ((sign * sum) <= 0 || INT_MAX < (sign * sum))
		return (FALSE);
	*dest = sign * sum;
	return (TRUE);
}

t_perrno	parsing(t_p_info *info, int ac, char **s)
{
	if (!is_digit_atoi(s[0], &info->philo_num))
		return (INVALID_ARGV);
	if (!is_digit_atoi(s[1], &info->time_to_die))
		return (INVALID_ARGV);
	if (!is_digit_atoi(s[2], &info->time_to_eat))
		return (INVALID_ARGV);
	if (!is_digit_atoi(s[3], &info->time_to_sleep))
		return (INVALID_ARGV);
	info->must_to_eat = -1;
	if (ac == 6 && !is_digit_atoi(s[4], &info->must_to_eat))
		return (INVALID_ARGV);
	return (OK);
}
