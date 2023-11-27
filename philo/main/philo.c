/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungmin <seungmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:20 by seungmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chk_arg(int argc, char **argv, t_arg *arg)
{
	if (!(argc == 5 || argc == 6))
		return (1);
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (arg->num_of_philo <= 0 || arg->time_to_die < 0
		|| arg->time_to_eat < 0 || arg->time_to_sleep < 0)
		return (1);
	arg->max_eat = 0;
	if (argc == 6)
	{
		arg->max_eat = ft_atoi(argv[5]);
		if (arg->max_eat < 0)
			return (1);
	}
	return (0);
}

void	init_philo(t_philo *philo, t_arg *arg)
{
	
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_arg	arg;

	if (chk_arg(argc, argv, &arg))
		return (1);
	init_philo(&philo, &arg);
	return (0);
}
