/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:08:16 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/31 16:19:30 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

static void	wait_rest_philos(t_pi *info, t_pwait *wait, int *seat)
{
	pthread_mutex_lock(&info->wait.ready_mutex);
	*seat = wait->ready;
	wait->ready++;
	pthread_mutex_unlock(&info->wait.ready_mutex);
	while (wait->ready >= 0);
	if (*seat % 2 == 1)
		philo_delay(&info->run, 0, info->eat_to_time / 2);
}

t_b	is_died_philo(t_pi *info, t_prun *run, int seat)
{
	long	current;

	current = philo_current(run);
	if (info->run.died)
		return (TRUE);
	if (philo_elapsed(run, run->philos[seat].last_eat) + info->eat_to_time > info->die_to_time)
	{
		pthread_mutex_lock(&run->printing);
		printf("current : %ld\n", current);
		printf("seat : %d\n", seat);
		printf("last_eat : %ld\n", run->philos[seat].last_eat);
		pthread_mutex_unlock(&run->printing);
		philo_printf(info, philo_elapsed(run, current), seat, "died");
		run->died = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void	*runing(void *av)
{
	int		seat;
	t_pi	*info;

	info = (t_pi *)av;
	wait_rest_philos(info, &info->wait, &seat);
	while (!info->must_eat || info->run.philos[seat].count_eat < info->must_eat)
	{
		philo_eat(info, &info->run, seat);
		philo_sleep(info, &info->run, seat);
		philo_printf(info, philo_current(&info->run), seat, "is thinking");
	}
	return (NULL);
}