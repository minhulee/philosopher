/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:17:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/30 17:13:39 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <unistd.h>

void	*runing(void *av)
{
	t_pi	*info;
	int		seat;

	info = (t_pi *)av;
	pthread_mutex_lock(&info->wait.ready_mutex);
	seat = info->wait.ready;
	info->wait.ready++;
	pthread_mutex_unlock(&info->wait.ready_mutex);
	pthread_mutex_lock(&info->wait.start_mutex);
	pthread_mutex_unlock(&info->wait.start_mutex);
	// - 한번에 시작해라 씹련들아. -
	if (seat % 2 == 1)
		usleep(info->eat_to_time / 4 * 1000);
	for (int i = 0; i < 10; i++)
	{
		philo_eat(info, &info->run, seat);
		philo_sleep(info, &info->run, seat);
		philo_printf(info, philo_current(&info->run), seat, "is thinking");
	}
	return (NULL);
}

void	start_thread(t_pi *info, t_pwait *wait, t_prun *run)
{
	struct timeval	time;

	while (1)
	{
		pthread_mutex_lock(&wait->ready_mutex);
		if (wait->ready == info->philo_num)
		{
			if (gettimeofday(&time, NULL) != 0)
				exit_err(OUT_OF_MEMORY);
			run->start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
			pthread_mutex_unlock(&wait->ready_mutex);
			pthread_mutex_unlock(&wait->start_mutex);
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

	count = 0;
	while (count < info->philo_num) // 들어온 수 만큼 쓰레드 생성
	{
		if (pthread_create(&run->philos[count], NULL, runing, (void *)info) != 0)
		{
			ft_printf("thread_faild..\n");
			exit(1);
		}
		count++;
	}
}

void	philo(t_pi *info, t_pwait *wait, t_prun *run)
{
	int	count;

	pthread_mutex_lock(&wait->start_mutex);
	make_forks(info, run);
	run->philos = ft_calloc(info->philo_num, sizeof(pthread_t));
	if (!run->philos)
		exit_err(OUT_OF_MEMORY);
	new_thread(info, run);
	start_thread(info, &info->wait, &info->run);

	count = 0;
	while (count < info->philo_num)
	{
		if (pthread_join(run->philos[count], NULL) != 0)
		{
			ft_printf("join failed..\n");
			exit(1);
		}
		count++;
	}
}
