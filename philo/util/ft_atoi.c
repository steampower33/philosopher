/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:13:48 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/21 16:36:50 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_func(const char *str, int start, int end)
{
	int	num;

	num = 0;
	while (start < end)
	{
		num = num * 10 + (str[start] - '0');
		start++;
	}
	return (num);
}

static int	ft_isspace(const char *str, int len)
{
	while (str[len])
	{
		if (!(str[len] == '\t' || str[len] == '\n' || str[len] == '\v'
				|| str[len] == '\f' || str[len] == '\r' || str[len] == ' '))
			break ;
		len++;
	}
	return (len);
}

static int	ft_issign(const char *str, int str_len, int *minus)
{
	int	sign_cnt;

	sign_cnt = 0;
	*minus = 1;
	while (str[str_len])
	{
		if (sign_cnt > 1)
			return (-1);
		if (str[str_len] == '-')
		{
			*minus = -1;
			sign_cnt++;
		}
		else if (str[str_len] == '+')
			sign_cnt++;
		else
			break ;
		str_len++;
	}
	return (str_len);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	str_idx;
	int	start_idx;

	str_idx = ft_isspace(str, 0);
	str_idx = ft_issign(str, str_idx, &minus);
	if (str_idx == -1)
		return (0);
	start_idx = str_idx;
	while (str[str_idx])
	{
		if (!ft_isdigit(str[str_idx]))
			break ;
		str_idx++;
	}
	return (minus * ft_atoi_func(str, start_idx, str_idx));
}
