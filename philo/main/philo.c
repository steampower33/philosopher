/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:18 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/22 18:58:37 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	chk_arg(int argc)
{
	if (!(argc == 5 || argc == 6))
		exit(1);
}

void	init_arg(int argc, char **argv, t_philo *philo)
{
	philo->num = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->max_eat = ft_atoi(argv[5]);
	
	printf("%d\n", ft_atoi(argv[1]));
	printf("%d\n", ft_atoi(argv[2]));
	printf("%d\n", ft_atoi(argv[3]));
	printf("%d\n", ft_atoi(argv[4]));
	if (argc == 6)
		printf("%u\n", ft_atoi(argv[5]));
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	chk_arg(argc);
	init_arg(argc, argv, &philo);
}
