/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:06:27 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/24 11:39:42 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <sys/fcntl.h>
#include <sys/semaphore.h>

void	init_sem(t_philo *philo)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("died");
	philo->fork = sem_open("fork", O_CREAT, 0644, philo->info->philo_num);
	if (philo->fork < 0)
		ft_err(INIT_SEM_FAIL);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	if (philo->print < 0)
	{
		sem_close(philo->fork);
		ft_err(INIT_SEM_FAIL);
	}
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		ft_err(BOOT_TIME_FAIL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_p_info	info;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		ft_err(OUT_OF_MEMORY);
	parsing(&info, ac, av + 1);
	philo->info = &info;
	init_sem(philo);
	info.booted = get_time();
	philo_bonus(philo);
	return (0);
}