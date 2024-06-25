/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:09:07 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 12:44:33 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	end_proc(pid_t *pid, t_philo philo)
{
	int	i;

	i = 0;
	while (i < philo.info->philo_num)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	sem_post(philo.print);
	free(pid);
	pid = NULL;
}

static void	parent(pid_t *pid, t_philo philo)
{
	int	seat;
	int	status;

	seat = 0;
	while (seat < philo.info->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			end_proc(pid, philo);
			return ;
		}
		else
			seat++;
	}
}

void	philo_bonus(t_philo philo, sem_t **died)
{
	int		seat;
	pid_t	*pid;

	pid = (pid_t *)malloc(philo.info->philo_num * sizeof(pid_t));
	if (!pid)
		ft_err(OUT_OF_MEMORY);
	seat = -1;
	while (++seat < philo.info->philo_num)
	{
		pid[seat] = fork();
		if (pid[seat] == 0)
		{
			philo.seat = seat;
			philo.died = died[seat];
			run(philo);
			return ;
		}
		else if (pid[seat] < 0)
		{
			end_proc(pid, philo);
			close_died(&died, philo.info->philo_num);
			ft_err(FORK_FAILED);
		}
	}
	parent(pid, philo);
}
