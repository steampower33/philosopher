/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/05 14:25:35 by seunlee2         ###   ########.fr       */
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
	if (!ft_strncmp(str, "died", 4))
		return ;
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
			pthread_mutex_unlock(&(*rsrc)->last_eat_time_mutex);
			philo_print(*rsrc, (*philo)[idx].id, "died");
			pthread_mutex_lock(&(*rsrc)->philo_stop_mutex);
			(*rsrc)->philo_stop = 1;
			pthread_mutex_unlock(&(*rsrc)->philo_stop_mutex);
			pthread_mutex_unlock(&(*rsrc)->print);
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
			pthread_mutex_unlock(&rsrc->philo_done_mutex);
			pthread_mutex_lock(&rsrc->philo_stop_mutex);
			rsrc->philo_stop = 1;
			pthread_mutex_unlock(&rsrc->philo_stop_mutex);
			printf("All Philosopher Are Full\n");
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
	free_rsrc(rsrc);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_resource	rsrc;

	if (init_rsrc(argc, argv, &rsrc))
		return (p_err("Argv init error", 1));
	if (init_mutex(&rsrc))
		return (p_err("Mutex init error", 1));
	if (init_philo(&philo, &rsrc))
		return (p_err("Philo init error", 1));
	if (start_philo(philo, &rsrc))
		return (p_err("Do philo error", 1));
	return (0);
}
