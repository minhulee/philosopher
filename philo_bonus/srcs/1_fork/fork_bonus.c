/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:09:07 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 14:41:12 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	end_proc(pid_t *pid, t_philo philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
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
			end_proc(pid, philo, philo.info->philo_num);
			return ;
		}
		else
			seat++;
	}
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
			end_proc(pid, philo, seat);
			close_died(&died, philo.info->philo_num);
			ft_err(FORK_FAILED, &philo);
		}
	}
	parent(pid, philo);
}
