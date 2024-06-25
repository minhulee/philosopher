/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 12:58:28 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	close_died(sem_t ***died, int size)
{
	sem_t	**target;
	int		i;

	target = *died;
	i = 0;
	while (i < size && target[i])
	{
		sem_close(target[i]);
		i++;
	}
	free(target);
	target = NULL;
}

char	*get_err_message(int errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	err[INIT_INFO_FAIL] = "Error\ninit info failed.. : ";
	err[INIT_SEM_FAIL] = "Error\ninit sem failed.. : ";
	err[BOOT_TIME_FAIL] = "Error\nget booted time failed.. : ";
	err[OUT_OF_MEMORY] = "Error\nout of memory.. : ";
	err[FORK_FAILED] = "Error\nfork main proc failed.. : ";
	err[PTHREAD_CREATE_FAIL] = "Error\npthread create failed.. : ";
	err[PTHREAD_JOIN_FAIL] = "Error\npthread join failed.. : ";
	err[GET_TIME_FAIL] = "Error\nget time failed.. : ";
	return (err[errno]);
}

void	ft_err(int errno)
{
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
