/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:09:07 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/24 11:18:04 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	ft_kill(pid_t *pid, int philo_num)
{
	int	count;

	count = 0;
	while (count < philo_num)
	{
		kill(pid[count], SIGKILL);
		count++;
	}
}

void	parent(pid_t *pid, int philo_num)
{
	int	seat;
	int	status;

	seat = 0;
	while (seat < philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			ft_kill(pid, philo_num);
			break ;
		}
		else
		{
			seat++;
		}
	}
}

void	philo_bonus(t_philo *philo) // n개의 프로세스가 생성되면, 복제된 n 개의 필로
{
	int		seat;
	pid_t	*pid;

	pid = (pid_t *)malloc(philo->info->philo_num * sizeof(pid_t));
	if (!pid)
		ft_err(OUT_OF_MEMORY);
	seat = -1;
	while (++seat < philo->info->philo_num)
	{
		pid[seat] = fork();
		if (pid[seat] == 0)
		{
			philo->seat = seat;
			run(philo);
			return ;
		}
		else if (pid[seat] < 0)
			ft_err(OUT_OF_MEMORY);
	}
	parent(pid, philo->info->philo_num);
}
