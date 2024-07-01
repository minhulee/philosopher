/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:22:09 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:40:04 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (FAIL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static t_perrno	init_info(t_p_info *info)
{
	info->booted = get_time();
	if (info->booted == FAIL)
		return (BOOT_TIME_FAIL);
	info->died = FALSE;
	info->start = FALSE;
	if (pthread_mutex_init(&info->start_mutex, NULL) < 0)
		return (INIT_INFO_FAIL);
	if (pthread_mutex_init(&info->died_mutex, NULL) < 0)
	{
		pthread_mutex_destroy(&info->start_mutex);
		return (INIT_INFO_FAIL);
	}
	if (pthread_mutex_init(&info->print_mutex, NULL) < 0)
	{
		pthread_mutex_destroy(&info->start_mutex);
		pthread_mutex_destroy(&info->died_mutex);
		return (INIT_INFO_FAIL);
	}
	return (OK);
}

int	main(int ac, char **av)
{
	t_p_info	info;
	t_perrno	errno;
	t_philo		*philos;

	if (!(ac == 5 || ac == 6))
		ft_err(INVALID_ARGV, NULL);
	errno = OK;
	philos = NULL;
	if (errno == OK)
		errno = parsing(&info, ac, av + 1);
	if (errno == OK)
		errno = init_info(&info);
	if (errno == OK)
		errno = init_philos(&philos, &info);
	if (errno == OK)
		errno = philo(philos);
	if (errno == OK)
		return (ft_exit(philos));
	else
		return (ft_err(errno, philos));
}
