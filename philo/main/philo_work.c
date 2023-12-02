/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:15:12 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/03 05:24:05 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_resource *rsrc, int id, char *str)
{
	long long	time;

	time = get_now();
	pthread_mutex_lock(&rsrc->print);
	if (rsrc->philo_stop != 1)
		printf("%lld %d %s\n", time - rsrc->time_to_start, id + 1, str);
	pthread_mutex_unlock(&rsrc->print);
}

void	philo_eat(t_philo *philo, t_resource *rsrc, int first, int second)
{
	pthread_mutex_lock(&rsrc->fork[first]);
	philo_print(rsrc, philo->id, "has taken a fork");
	if (rsrc->num_of_philo != 1)
	{
		pthread_mutex_lock(&rsrc->fork[second]);
		philo_print(rsrc, philo->id, "has taken a fork");
		philo_print(rsrc, philo->id, "is eating");
		philo->last_eat_time = get_now();
		philo->cnt_to_eat += 1;
		spend_time(rsrc, rsrc->time_to_eat);
		pthread_mutex_unlock(&rsrc->fork[second]);
	}
	pthread_mutex_unlock(&rsrc->fork[first]);
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

void	*philo_work(void *argv)
{
	t_philo		*philo;
	t_resource	*rsrc;

	philo = argv;
	rsrc = philo->rsrc;
	while (rsrc->philo_stop != 1)
	{
		if (philo->id % 2 == 1)
			usleep(500);
		philo_eat(philo, rsrc, philo->right, philo->left);
		if (rsrc->max_eat == philo->cnt_to_eat)
		{
			rsrc->philo_done += 1;
			break ;
		}
		philo_sleep(philo, rsrc);
		philo_think(philo, rsrc);
	}
	return (NULL);
}
