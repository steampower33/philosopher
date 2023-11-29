/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/29 21:08:13 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, char **argv, t_resource *rsrc)
{
	if (!(argc == 5 || argc == 6))
		return (1);
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
		if (rsrc->max_eat < 0)
			return (1);
	}
	return (0);
}

int	init_philo(t_philo **philo, t_resource *rsrc)
{
	int	idx;

	*philo = (t_philo *)malloc(sizeof(t_philo) * rsrc->num_of_philo);
	if (!(*philo))
		return (1);
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

int	destroy_mutex(t_resource *rsrc, int last)
{
	pthread_mutex_destroy(&(rsrc->print));
	while (0 <= last)
	{
		pthread_mutex_destroy(&(rsrc->fork[last]));
		last--;
	}
	pthread_mutex_destroy(rsrc->fork);
	return (1);
}

int	init_mutex(t_resource *rsrc)
{
	int	idx;

	if (pthread_mutex_init(&(rsrc->print), NULL))
		return (1);
	rsrc->fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * rsrc->num_of_philo);
	if (!(rsrc->fork))
		return (1);
	idx = 0;
	while (idx < rsrc->num_of_philo)
	{
		if (pthread_mutex_init(&(rsrc->fork[idx]), NULL))
			return (destroy_mutex(rsrc, idx));
		if (idx == 4)
			return (destroy_mutex(rsrc, idx));
		idx++;
	}
	return (0);
}



int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_resource	rsrc;

	if (check_arguments(argc, argv, &rsrc))
		return (error_handler("arguments error", 1));
	if (init_mutex(&rsrc))
		return (error_handler("mutex init error", 1));
	if (init_philo(&philo, &rsrc))
		return (error_handler("philo init error", 1));
	// int	idx = 0;
	// while (idx < rsrc.num_of_philo)
	// 	printf("%d\n", philo[idx++].id);
	return (0);
}
