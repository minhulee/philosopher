/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/24 09:51:25 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

char	*get_err_message(int errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	err[BOOT_TIME_FAIL] = "Error\nget booted time failed.. : ";
	err[INIT_INFO_FAIL] = "Error\ninit info failed.. : ";
	err[INIT_SEM_FAIL] = "Error\ninit sem failed.. : ";
	err[OUT_OF_MEMORY] = "Error\nout of memory.. : ";
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
