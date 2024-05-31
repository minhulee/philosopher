/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:41:25 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/31 08:53:08 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

void	philo_delay(t_prun *run, long start, long end)
{
	while (philo_elapsed(run, start) < end)
		usleep(100);
	return ;
}

void	philo_printf(t_pi *info, long time, int seat, char *s)
{
	pthread_mutex_lock(&info->run.printing);
	printf("%ld %d %s\n", time, seat + 1, s);
	pthread_mutex_unlock(&info->run.printing);
}

// start를 받아서 지난 시간을 측정하는 함수

long	philo_current(t_prun *run)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) != 0)
		exit_err(OUT_OF_MEMORY);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - run->start);
}

long	philo_elapsed(t_prun *run, long start)
{
	return (philo_current(run) - start);
}
