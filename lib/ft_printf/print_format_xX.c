/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_xX.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:39:25 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/14 16:18:05 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format_xux(char s, unsigned int x)
{
	size_t	count;
	char	*base_form;

	count = 0;
	if (s == 'x')
		base_form = HEXA_BASE;
	else
		base_form = HEXA_U_BASE;
	if (print_nbr_base(&count, x, HEXA, base_form) < 0)
		return (E);
	return (count);
}
