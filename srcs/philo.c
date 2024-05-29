/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:44:09 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 04:20:05 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/philo_err.h"
#include <sys/select.h>

static void	init_info(t_pi *info)
{
	info->philo = 0;
	info->eat = 0;
	info->sleep = 0;
	info->dead = 0;
	info->must = 0;
	info->errno = OK;
	info->ready = 0;
	if (gettimeofday(&info->start_time, NULL) != 0)
		exit_err(OUT_OF_MEMORY);
	pthread_mutex_init(&info->ready_mutex, NULL);
	pthread_mutex_init(&info->sleeping, NULL);
	pthread_mutex_init(&info->thinking, NULL);
}

int	main(int ac, char **av)
{
	t_pi	info;

	if (ac != 5 && ac != 6)
		exit_err(INVALID_ARGV);
	init_info(&info);
	parsing(&info, ac, av + 1);
	new_thread(&info);

	exit(0);
}
