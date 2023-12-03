/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/03 15:45:38 by seunlee2         ###   ########.fr       */
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

void	is_philo_dead_while(t_philo **philo, t_resource **rsrc)
{
	int	idx;

	idx = 0;
	while (idx < (*rsrc)->num_of_philo)
	{
		pthread_mutex_lock(&(*rsrc)->last_eat_time_mutex);
		if ((get_now() - (*philo)[idx].last_eat_time) >= (*rsrc)->time_to_die)
		{
			philo_print(*rsrc, (*philo)[idx].id, "died");
			pthread_mutex_lock(&(*rsrc)->philo_stop_mutex);
			(*rsrc)->philo_stop = 1;
			pthread_mutex_unlock(&(*rsrc)->philo_stop_mutex);
			pthread_mutex_unlock(&(*rsrc)->last_eat_time_mutex);
			return ;
		}
		pthread_mutex_unlock(&(*rsrc)->last_eat_time_mutex);
		idx++;
	}
}

void	is_philo_dead(t_philo *philo, t_resource *rsrc)
{
	while (rsrc->philo_stop != 1)
	{
		pthread_mutex_lock(&rsrc->philo_done_mutex);
		if ((rsrc->max_eat != 0) && (rsrc->num_of_philo == rsrc->philo_done))
		{
			rsrc->philo_stop = 1;
			printf("All Philosopher Are Full\n");
			pthread_mutex_unlock(&rsrc->philo_done_mutex);
			break ;
		}
		pthread_mutex_unlock(&rsrc->philo_done_mutex);
		is_philo_dead_while(&philo, &rsrc);
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
