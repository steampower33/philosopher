/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:48:37 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/05 13:58:05 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;

	if (n == 0)
		return (0);
	len = 0;
	while ((s1[len] != '\0' && s2[len] != '\0'))
	{
		if (s1[len] != s2[len])
			break ;
		len++;
		if (len == n)
			return (0);
	}
	return ((unsigned char)s1[len] - (unsigned char)s2[len]);
}
