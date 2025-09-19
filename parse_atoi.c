/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:36:36 by giomastr          #+#    #+#             */
/*   Updated: 2025/08/25 18:30:45 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sign_check(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (!isitdigit(str[i]))
			return (0);
	}
	return (sign);
}

int	parse_atoi(const char *str)
{
	int		i;
	int		sign;
	int		temp;
	int		result;

	sign = sign_check(str);
	if (sign == 0)
		return (0);
	i = 0;
	result = 0;
	while (str[i] && isitdigit(str[i]))
	{
		temp = result;
		result = (result * 10) + (str[i] - '0');
		if (result / 10 != temp)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	result = result * sign;
	return (result);
}
