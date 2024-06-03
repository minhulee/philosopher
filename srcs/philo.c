/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jangeun-ji <jangeun-ji@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:44:09 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/03 10:49:51 by jangeun-ji       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/philo_err.h"
#include <sys/select.h>

static void	init_info(t_pi *info, t_pwait *wait, t_prun *run)
{
	info->philo_num = 0;
	info->eat_to_time = 0;
	info->sleep_to_time = 0;
	info->die_to_time = 0;
	info->must_eat = 0;
	info->errno = OK;
	wait->ready = 0;
	pthread_mutex_init(&wait->ready_mutex, NULL);
	run->died = FALSE;
	pthread_mutex_init(&run->died_mutex, NULL);
	pthread_mutex_init(&run->printing, NULL);
}

int	main(int ac, char **av)
{
	t_pi	info;

	if (ac != 5 && ac != 6)
		exit_err(INVALID_ARGV);
	init_info(&info, &info.wait, &info.run);
	parsing(&info, ac, av + 1);
	philo(&info, &info.wait, &info.run);

	exit(0);
}
