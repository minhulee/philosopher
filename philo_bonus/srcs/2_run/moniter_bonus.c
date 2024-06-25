/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:42:13 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:09:01 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <sys/semaphore.h>

void	*monitering(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	while (1)
	{
		sem_wait(philo->died);
		if (philo_current(*philo) - philo->last_eat > philo->info->time_to_die)
		{
			sem_post(philo->died);
			sem_wait(philo->print);
			printf("%ld %d %s\n", philo_current(*philo),
				philo->seat + 1, "died");
			exit(1);
		}
		sem_post(philo->died);
		usleep(300);
	}
}
