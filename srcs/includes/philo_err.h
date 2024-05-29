/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_err.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:02 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/28 21:49:39 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERR_H
# define PHILO_ERR_H

# define ERRMAX 1
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef enum e_philo_errno
{
	OK = -1,
	INVALID_ARGV,
	OUT_OF_MEMORY,
	NOT_DIGIT,
	NOT_INTEGER
}	t_perrno;

#endif