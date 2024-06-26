/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 14:26:05 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	close_died(sem_t ***died, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		sem_close((*died)[i]);
		i++;
	}
	free(*died);
	*died = NULL;
}

char	*get_err_message(int errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	err[INIT_SEM_FAIL] = "Error\ninit sem failed.. : ";
	err[BOOT_TIME_FAIL] = "Error\nget booted time failed.. : ";
	err[OUT_OF_MEMORY] = "Error\nout of memory.. : ";
	err[FORK_FAILED] = "Error\nfork main proc failed.. : ";
	return (err[errno]);
}

void	ft_err(int errno, void *av)
{
	t_philo	*philo;

	if (av != NULL)
	{
		philo = (t_philo *)av;
		sem_close(philo->print);
		sem_close(philo->fork);
	}
	printf("%s%d\n", get_err_message(errno), errno);
	exit(1);
}

void	ft_exit(t_philo philo, sem_t **died)
{
	sem_close(philo.print);
	sem_close(philo.fork);
	close_died(&died, philo.info->philo_num);
	exit(0);
}
