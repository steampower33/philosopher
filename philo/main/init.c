/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:48:00 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/08 14:13:08 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_argv(int argc, char **argv, t_resource *rsrc)
{
	if (!(argc == 5 || argc == 6))
		return (1);
	rsrc->time_to_start = get_now();
	rsrc->num_of_philo = ft_atoi(argv[1]);
	rsrc->time_to_die = ft_atoi(argv[2]);
	rsrc->time_to_eat = ft_atoi(argv[3]);
	rsrc->time_to_sleep = ft_atoi(argv[4]);
	if (rsrc->num_of_philo <= 0 || rsrc->time_to_die < 0
		|| rsrc->time_to_eat < 0 || rsrc->time_to_sleep < 0)
		return (1);
	rsrc->max_eat = 0;
	if (argc == 6)
	{
		rsrc->max_eat = ft_atoi(argv[5]);
		if (rsrc->max_eat <= 0)
			return (1);
	}
	return (0);
}

int	init_rsrc(int argc, char **argv, t_resource *rsrc)
{
	if (!memset(rsrc, 0, sizeof(t_resource)))
		return (1);
	if (init_argv(argc, argv, rsrc))
		return (1);
	rsrc->philo_done = 0;
	rsrc->philo_stop = 0;
	rsrc->forks = (int *)malloc(sizeof(int) * rsrc->num_of_philo);
	if (!rsrc->forks)
		return (1);
	if (!memset(rsrc->forks, -1, rsrc->num_of_philo))
		return (1);
	return (0);
}

int	init_mutex(t_resource *rsrc)
{
	int	idx;
	int	flag;

	flag = 0;
	flag += pthread_mutex_init(&rsrc->print, NULL);
	flag += pthread_mutex_init(&rsrc->last_eat_time_mutex, NULL);
	flag += pthread_mutex_init(&rsrc->philo_stop_mutex, NULL);
	flag += pthread_mutex_init(&rsrc->philo_done_mutex, NULL);
	rsrc->forks_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * rsrc->num_of_philo);
	flag += !rsrc->forks_mutex;
	idx = 0;
	while (!flag && idx < rsrc->num_of_philo)
	{
		flag += pthread_mutex_init(&rsrc->forks_mutex[idx], NULL);
		idx++;
	}
	if (flag >= 1)
	{
		free_rsrc(rsrc);
		return (1);
	}
	return (0);
}

int	init_philo(t_philo **philo, t_resource *rsrc)
{
	int	idx;

	*philo = (t_philo *)malloc(sizeof(t_philo) * rsrc->num_of_philo);
	if (!(*philo))
	{
		free_rsrc(rsrc);
		return (1);
	}
	idx = 0;
	while (idx < rsrc->num_of_philo)
	{
		(*philo)[idx].rsrc = rsrc;
		(*philo)[idx].id = idx;
		(*philo)[idx].left = idx;
		(*philo)[idx].right = (idx + 1) % rsrc->num_of_philo;
		(*philo)[idx].cnt_to_eat = 0;
		idx++;
	}
	return (0);
}
