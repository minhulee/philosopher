/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:17:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 12:06:19 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <unistd.h>

long	philo_time(struct timeval start)
{
	struct timeval	end;
	long			s;
	long			us;
	double			ms;

	gettimeofday(&end, NULL);
	s  = end.tv_sec  - start.tv_sec;
	us = end.tv_usec - start.tv_usec;
	ms = (s * 1000 + us / 1000.0);
	return (ms);
}

void	*temp(void *av)
{
	t_pi	*info;
	int		tid;
	int		res;
	struct timeval	time;

	info = (t_pi *)av;
	pthread_mutex_lock(&info->ready_mutex);
	info->ready++;
	tid = info->ready;
	pthread_mutex_unlock(&info->ready_mutex);
	while (1)
	{
		if (info->ready < 0)
			break ;
	}
	if (gettimeofday(&time, NULL) != 0)
		exit(1);
	philo_sleep(info, tid, time);
	return (NULL);
}

void	start_thread(t_pi *info)
{
	while (1)
	{
		if (info->ready == info->philo)
		{
			pthread_mutex_lock(&info->ready_mutex);
			info->ready = -1;
			pthread_mutex_unlock(&info->ready_mutex);
			break ;
		}
	}
}

void	new_thread(t_pi *info)
{
	int	count;

	info->forks = ft_calloc(info->philo, sizeof(t_b));
	if (!info->forks)
		exit_err(OUT_OF_MEMORY);
	info->fork_mutex = ft_calloc(info->philo, sizeof(pthread_mutex_t));
	if (!info->fork_mutex)
		exit_err(OUT_OF_MEMORY);


	count = 0;
	while (count < info->philo)
	{
		pthread_mutex_init(&info->fork_mutex[count], NULL);
		count++;
	}

	ft_printf("%ld\n", info->start_time.tv_sec);

	info->philos = ft_calloc(info->philo, sizeof(pthread_t));
	if (!info->philos)
		exit_err(OUT_OF_MEMORY);
	count = 0;
	while (count < info->philo) // 들어온 수 만큼 쓰레드 생성
	{
		if (pthread_create(&info->philos[count], NULL, temp, (void *)info) != 0)
		{
			ft_printf("thread_faild..\n");
			exit(1);
		}
		count++;
	}

	start_thread(info);

	count = 0;
	while (count < info->philo)
	{
		if (pthread_join(info->philos[count], NULL) != 0)
		{
			ft_printf("join failed..\n");
			exit(1);
		}
		count++;
	}
}