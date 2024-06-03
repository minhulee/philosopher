/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jangeun-ji <jangeun-ji@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:17:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/03 11:14:04 by jangeun-ji       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_pthread/_pthread_t.h>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <unistd.h>

void	start_thread(t_pi *info, t_pwait *wait, t_prun *run)
{
	struct timeval	time;

	while (1)
	{
		pthread_mutex_lock(&wait->ready_mutex);
		if (wait->ready == info->philo_num)
		{
			pthread_mutex_lock(&run->printing);
			pthread_mutex_unlock(&run->printing);
			if (gettimeofday(&time, NULL) != 0)
				exit_err(GET_TIME_FAIL);
			run->start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
			info->wait.ready = -1;
			pthread_mutex_unlock(&wait->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&wait->ready_mutex);
		usleep(100);
	}
}

static void	make_forks(t_pi *info, t_prun *run)
{
	int	count;

	run->forks = ft_calloc(info->philo_num, sizeof(t_b));
	if (!run->forks)
		exit_err(OUT_OF_MEMORY);
	run->fork_mutex = ft_calloc(info->philo_num, sizeof(pthread_mutex_t));
	if (!run->fork_mutex)
		exit_err(OUT_OF_MEMORY);
	count = 0;
	while (count < info->philo_num)
	{
		run->forks[count] = FALSE;
		pthread_mutex_init(&run->fork_mutex[count], NULL);
		count++;
	}
}

static void	new_thread(t_pi *info, t_prun *run)
{
	int	count;

	run->philos_t = (pthread_t *)ft_calloc(info->philo_num, sizeof(pthread_t));
	if (!run->philos)
		exit_err(OUT_OF_MEMORY);
	run->philos = (t_p *)ft_calloc(info->philo_num, sizeof(t_p));
	if (!run->philos)
		exit_err(OUT_OF_MEMORY);
	count = 0;
	while (count < info->philo_num)
	{
		if (pthread_create(&run->philos_t[count], NULL, runing, (void *)info) != 0)
			exit_err(THREAD_CREATE_FAIL);
		run->philos[count].count_eat = 0;
		run->philos[count].last_eat = 0;
		count++;
	}
}

static void	thread_join(t_pi *info, t_prun *run)
{
	int	count;

	count = 0;
	while (count < info->philo_num)
	{
		if (pthread_join(run->philos_t[count], NULL) != 0)
		{
			ft_printf("join failed..\n");
			exit(1);
		}
		count++;
	}
}

void	philo(t_pi *info, t_pwait *wait, t_prun *run)
{
	make_forks(info, run);
	run->philos = ft_calloc(info->philo_num, sizeof(pthread_t));
	if (!run->philos)
		exit_err(OUT_OF_MEMORY);
	new_thread(info, run);
	start_thread(info, wait, run);
	thread_join(info, run);
}
