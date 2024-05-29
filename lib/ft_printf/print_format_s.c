/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/14 16:17:44 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format_s(char *s)
{
	size_t	count;

	if (!s)
		s = "(null)";
	count = 0;
	while (s[count])
	{
		if (write(1, &s[count], 1) < 0)
			return (E);
		count++;
	}
	return (count);
}
