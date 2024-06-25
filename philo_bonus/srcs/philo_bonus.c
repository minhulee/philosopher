/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:06:27 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 12:44:13 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <sys/semaphore.h>

static sem_t	**init_died_sem(int philo_num)
{
	sem_t	**died;
	int		i;
	char	*s;

	died = (sem_t **)malloc(sizeof(sem_t *) * philo_num);
	if (!died)
		ft_err(OUT_OF_MEMORY);
	memset(died, 0, sizeof(sem_t *) * philo_num);
	i = -1;
	while (++i < philo_num)
	{
		s = ft_ltoa(i);
		if (!s)
			break ;
		sem_unlink(s);
		died[i] = sem_open(s, O_CREAT, 0644, 1);
		free(s);
		if (died[i] == SEM_FAILED)
			break ;
	}
	if (i != philo_num)
		close_died(&died, i - 1);
	return (died);
}

void	init_sem(t_philo *philo, sem_t ***died)
{
	sem_unlink("fork");
	sem_unlink("print");
	philo->fork = sem_open("fork", O_CREAT, 0644, philo->info->philo_num);
	if (philo->fork == SEM_FAILED)
	{
		close_died(died, philo->info->philo_num);
		ft_err(INIT_SEM_FAIL);
	}
	philo->print = sem_open("print", O_CREAT, 0644, 1);
	if (philo->print == SEM_FAILED)
	{
		close_died(died, philo->info->philo_num);
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
	t_philo		philo;
	sem_t		**died;

	if (!(ac == 5 || ac == 6))
		ft_err(INVALID_ARGV);
	died = NULL;
	memset(&info, 0, sizeof(t_p_info));
	memset(&philo, 0, sizeof(t_philo));
	parsing(&info, ac, av + 1);
	philo.info = &info;
	died = init_died_sem(info.philo_num);
	if (!died)
		ft_err(INIT_SEM_FAIL);
	init_sem(&philo, &died);
	info.booted = get_time();
	philo_bonus(philo, died);
	ft_exit(philo, died);
	return (0);
}
