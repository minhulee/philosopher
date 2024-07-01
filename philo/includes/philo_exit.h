/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:02 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:06:52 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_EXIT_H
# define PHILO_EXIT_H

# define ERRMAX 7
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_philo_errno
{
	OK = -1,
	INVALID_ARGV,
	BOOT_TIME_FAIL,
	INIT_INFO_FAIL,
	INIT_PHILO_FAIL,
	INIT_FORK_FAIL,
	CREATE_PTHREAD_FAIL,
	GET_TIME_FAIL
}	t_perrno;

#endif