/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 12:53:26 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>

# include "./philo_exit_bonus.h"

typedef enum e_bool
{
	FAIL = -1,
	FALSE,
	TRUE
}	t_b;

typedef struct s_philo_info
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_to_eat;
	long			booted;
}	t_p_info;

typedef struct s_philo
{
	int			seat;
	int			count_eat;
	long		last_eat;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*died;
	t_p_info	*info;
}	t_philo;

/* philo */
long	get_time(void);
void	close_died(sem_t ***died, int size);
void	ft_mutex_init(pthread_mutex_t *mutex);

/* parse */
void	parsing(t_p_info *info, int ac, char **s);

/* fork */
void	philo_bonus(t_philo philo, sem_t **died);

/* run */
void	*monitering(void *av);
void	run(t_philo philo);

/* util */
void	philo_delay(t_philo philo, long start, long limit);
long	philo_current(t_philo philo);
void	philo_printf(t_philo philo, char *s);

/* philo_err */
void	ft_err(int errno);
void	ft_exit(t_philo philo, sem_t **died);

/* ltoa */
char	*ft_ltoa(long n);

#endif