/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:09:07 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 11:08:05 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	end_process(pid_t *pid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	free(pid);
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
			end_process(pid, philo.info->philo_num);
			sem_post(philo.print);
			return ;
		}
		else
			seat++;
	}
	free(pid);
}

static void	child(int seat, t_philo philo, sem_t **died)
{
	philo.seat = seat;
	philo.died = died[seat];
	run(philo);
}

void	philo_bonus(t_philo philo, sem_t **died)
{
	int		seat;
	pid_t	*pid;

	pid = (pid_t *)malloc(philo.info->philo_num * sizeof(pid_t));
	if (!pid)
	{
		close_died(&died, philo.info->philo_num);
		ft_err(OUT_OF_MEMORY, &philo);
	}
	seat = -1;
	while (++seat < philo.info->philo_num)
	{
		pid[seat] = fork();
		if (pid[seat] == 0)
			child(seat, philo, died);
		else if (pid[seat] < 0)
		{
			end_process(pid, seat);
			close_died(&died, philo.info->philo_num);
			ft_err(FORK_FAILED, &philo);
		}
	}
	parent(pid, philo);
}
