/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:15:12 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/03 15:39:18 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo, t_resource *rsrc)
{
	pthread_mutex_lock(&rsrc->fork[philo->left]);
	philo_print(rsrc, philo->id, "has taken a fork");
	if (rsrc->num_of_philo != 1)
	{
		pthread_mutex_lock(&rsrc->fork[philo->right]);
		philo_print(rsrc, philo->id, "has taken a fork");
		philo_print(rsrc, philo->id, "is eating");
		pthread_mutex_lock(&rsrc->last_eat_time_mutex);
		philo->last_eat_time = get_now();
		pthread_mutex_unlock(&rsrc->last_eat_time_mutex);
		philo->cnt_to_eat += 1;
		spend_time(rsrc, rsrc->time_to_eat);
		pthread_mutex_unlock(&rsrc->fork[philo->right]);
	}
	pthread_mutex_unlock(&rsrc->fork[philo->left]);
}

void	philo_sleep(t_philo *philo, t_resource *rsrc)
{
	philo_print(rsrc, philo->id, "is sleeping");
	spend_time(rsrc, rsrc->time_to_sleep);
}

void	philo_think(t_philo *philo, t_resource *rsrc)
{
	philo_print(rsrc, philo->id, "is thinking");
}

int	is_philo_stop(t_resource *rsrc)
{
	pthread_mutex_lock(&rsrc->philo_stop_mutex);
	if (rsrc->philo_stop == 1)
	{
		pthread_mutex_unlock(&rsrc->philo_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&rsrc->philo_stop_mutex);
	return (0);
}

void	*philo_work(void *argv)
{
	t_philo		*philo;
	t_resource	*rsrc;

	philo = argv;
	rsrc = philo->rsrc;
	while (1)
	{
		if (is_philo_stop(rsrc))
			break ;
		if (philo->id % 2 == 1)
			usleep(500);
		philo_eat(philo, rsrc);
		if (rsrc->num_of_philo == 1)
			spend_time(rsrc, rsrc->time_to_sleep);
		if (rsrc->max_eat == philo->cnt_to_eat)
		{
			pthread_mutex_lock(&rsrc->philo_done_mutex);
			rsrc->philo_done += 1;
			pthread_mutex_unlock(&rsrc->philo_done_mutex);
			break ;
		}
		philo_sleep(philo, rsrc);
		philo_think(philo, rsrc);
	}
	return (NULL);
}
