/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:02 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:08:43 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_EXIT_BONUS_H
# define PHILO_EXIT_BONUS_H

# define ERRMAX 9
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_philo_errno
{
	INVALID_ARGV = 0,
	INIT_INFO_FAIL,
	INIT_SEM_FAIL,
	BOOT_TIME_FAIL,
	OUT_OF_MEMORY,
	FORK_FAILED,
	PTHREAD_CREATE_FAIL,
	PTHREAD_JOIN_FAIL,
	GET_TIME_FAIL
}	t_perrno;

#endif