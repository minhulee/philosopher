/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:22:09 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:11:04 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check(void)
{
	system("leaks philo");
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		ft_err(BOOT_TIME_FAIL, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	init_info(t_p_info *info)
{
	info->booted = get_time();
	info->died = FALSE;
	if (pthread_mutex_init(&info->died_mutex, NULL) < 0)
		ft_err(INIT_INFO_FAIL, NULL);
	if (pthread_mutex_init(&info->print_mutex, NULL) < 0)
	{
		pthread_mutex_destroy(&info->died_mutex);
		ft_err(INIT_INFO_FAIL, NULL);
	}
}

int	main(int ac, char **av)
{
	t_p_info	info;

	if (!(ac == 5 || ac == 6))
		ft_err(INVALID_ARGV, NULL);
	parsing(&info, ac, av + 1);
	init_info(&info);
	philo(&info);
	return (0);
}
