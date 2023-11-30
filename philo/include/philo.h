/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:37 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/30 17:22:44 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t			thread;
	struct s_resource	*rsrc;
	int					id;
	int					left;
	int					right;
	int					cnt_to_eat;
}	t_philo;

typedef struct s_resource
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					philo_done;
}	t_resource;

int		init_rsrc(int argc, char **argv, t_resource *rsrc);
int		init_philo(t_philo **philo, t_resource *rsrc);
int		init_mutex(t_resource *rsrc);

void	do_work(t_philo *philo, t_resource *rsrc);
void	*do_thread(void	*argv);
int		do_philo(t_philo *philo, t_resource *rsrc);

void	join_pthread(t_philo *philo);
int		detach_pthread(t_philo *philo, int last);
int		destroy_mutex(t_resource *rsrc, int last);
void	free_all(t_resource *rsrc);

int		ft_atoi(const char *str);

int		error_handler(char *str, int error_code);
#endif