/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:46:57 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/05 13:49:45 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	detach_pthread(t_philo *philo, int last)
{
	while (0 < last)
	{
		pthread_detach(philo[last].thread);
		last--;
	}
	return (1);
}

void	join_pthread(t_philo *philo)
{
	int	idx;

	idx = 0;
	while (idx < philo->rsrc->num_of_philo)
		pthread_join(philo[idx++].thread, NULL);
	free(philo);
}

void	free_rsrc(t_resource *rsrc)
{
	int	idx;

	if (rsrc->forks)
		free(rsrc->forks);
	if (rsrc->forks_mutex)
	{
		idx = 0;
		while (idx < rsrc->num_of_philo)
			pthread_mutex_destroy(&rsrc->forks_mutex[idx++]);
		free(rsrc->forks_mutex);
	}
	pthread_mutex_destroy(&rsrc->print);
	pthread_mutex_destroy(&rsrc->last_eat_time_mutex);
	pthread_mutex_destroy(&rsrc->philo_done_mutex);
	pthread_mutex_destroy(&rsrc->philo_stop_mutex);
}
