/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/03 01:33:38 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_philo_dead(t_philo *philo, t_resource *rsrc)
{
	int	idx;

	while (rsrc->philo_stop != 1)
	{
		if ((rsrc->max_eat != 0) && (rsrc->num_of_philo == rsrc->philo_done))
		{
			rsrc->philo_stop = 1;
			printf("All Philosopher Are Full\n");
		}
		idx = 0;
		while (idx < rsrc->num_of_philo)
		{
			if ((get_now() - philo[idx].last_eat_time) >= rsrc->time_to_die)
			{
				philo_print(rsrc, philo[idx].id, "died");
				rsrc->philo_stop = 1;
			}
			idx++;
		}
	}
}

int	start_philo(t_philo *philo, t_resource *rsrc)
{
	int	idx;

	idx = 0;
	while (idx < rsrc->num_of_philo)
	{
		philo[idx].last_eat_time = get_now();
		if (pthread_create(&philo[idx].thread,
				NULL, philo_work, (void *)&philo[idx]))
			return (detach_pthread(philo, idx));
		idx++;
	}
	is_philo_dead(philo, rsrc);
	join_pthread(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_resource	rsrc;

	if (init_rsrc(argc, argv, &rsrc))
		return (error_handler("Arguments error", 1));
	if (init_mutex(&rsrc))
		return (error_handler("Mutex init error", 1));
	if (init_philo(&philo, &rsrc))
		return (error_handler("Philo init error", 1));
	if (start_philo(philo, &rsrc))
		return (error_handler("Do philo error", 1));
	free_all(&rsrc);
	return (0);
}
