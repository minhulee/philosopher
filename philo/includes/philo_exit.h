/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:02 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 13:08:31 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_EXIT_H
# define PHILO_EXIT_H

# define ERRMAX 8
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_philo_errno
{
	INVALID_ARGV = 0,
	BOOT_TIME_FAIL,
	INIT_INFO_FAIL,
	OUT_OF_MEMORY,
	INIT_FORK_FAIL,
	GET_TIME_FAIL
}	t_perrno;

#endif