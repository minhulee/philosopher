/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/28 17:45:45 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*get_err_message(int errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	return (err[errno]);
}

void	exit_err(int errno)
{
	ft_putstr_fd(get_err_message(errno), STDERR_FILENO);
	ft_putnbr_fd(errno, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}