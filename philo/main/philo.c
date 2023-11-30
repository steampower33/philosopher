/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/30 21:23:58 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_philo *philo, t_resource *rsrc)
{
	int	idx;

	idx = 0;
	while (idx < rsrc->num_of_philo)
	{
		philo[idx].last_eat_time = get_time();
		if (pthread_create(&philo[idx].thread,
				NULL, philo_work, (void *)&philo[idx]))
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

	if (init_rsrc(argc, argv, &rsrc))
		return (error_handler("arguments error", 1));
	if (init_mutex(&rsrc))
		return (error_handler("mutex init error", 1));
	if (init_philo(&philo, &rsrc))
		return (error_handler("philo init error", 1));
	if (start_philo(philo, &rsrc))
		return (error_handler("do philo error", 1));
	free_all(&rsrc);
	return (0);
}
