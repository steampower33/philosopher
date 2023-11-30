/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/30 17:25:48 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_work(t_philo *philo, t_resource *rsrc)
{
	pthread_mutex_lock(&rsrc->fork[philo->left]);
	// print
	if (rsrc->num_of_philo != 1)
	{
		// right
	}
	pthread_mutex_unlock(&rsrc->fork[philo->left]);
}

void	*do_thread(void	*argv)
{
	t_philo		*philo;
	t_resource	*rsrc;

	philo = argv;
	rsrc = philo->rsrc;
	while (rsrc->philo_done != 0)
	{
		do_work(philo, rsrc);
	}
	return (NULL);
}

int	do_philo(t_philo *philo, t_resource *rsrc)
{
	int	idx;

	idx = 0;
	while (idx < rsrc->num_of_philo)
	{
		if (pthread_create(&philo[idx].thread,
				NULL, do_thread, (void *)&philo[idx]))
			return (detach_pthread(philo, idx));
		idx++;
	}
	join_pthread(philo);
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
	if (do_philo(philo, &rsrc))
		return (error_handler("do philo error", 1));
	free_all(&rsrc);
	// system("leaks philo");
	return (0);
}
