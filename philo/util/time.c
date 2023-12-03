/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:11:22 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/03 09:20:52 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spend_time(t_resource *rsrc, long long time_to_spend)
{
	long long	start;
	long long	now;

	start = get_now();
	while (1)
	{
		pthread_mutex_lock(&rsrc->philo_stop_mutex);
		if (rsrc->philo_stop == 1)
		{
			pthread_mutex_unlock(&rsrc->philo_stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&rsrc->philo_stop_mutex);
		now = get_now();
		if ((now - start) >= time_to_spend)
			break ;
		usleep(rsrc->num_of_philo);
	}
}

long long	get_now(void)
{
	struct timeval	time;
	long long		now;

	gettimeofday(&time, 0);
	now = time.tv_sec * 1000 + time.tv_usec * 0.001;
	return (now);
}
