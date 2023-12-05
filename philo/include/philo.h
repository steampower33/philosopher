/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:37 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/05 13:58:31 by seunlee2         ###   ########.fr       */
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
	long long			last_eat_time;
}	t_philo;

typedef struct s_resource
{
	int					*forks;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		print;
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					philo_done;
	pthread_mutex_t		philo_done_mutex;
	int					philo_stop;
	pthread_mutex_t		philo_stop_mutex;
	long long			time_to_start;
	pthread_mutex_t		last_eat_time_mutex;
}	t_resource;

int			init_argv(int argc, char **argv, t_resource *rsrc);
int			init_rsrc(int argc, char **argv, t_resource *rsrc);
int			init_philo(t_philo **philo, t_resource *rsrc);
int			init_mutex(t_resource *rsrc);

void		philo_print(t_resource *rsrc, int id, char *str);
void		philo_eat(t_philo *philo, t_resource *rsrc);
void		philo_sleep(t_philo *philo, t_resource *rsrc);
void		philo_think(t_philo *philo, t_resource *rsrc);

void		is_philo_dead_while(t_philo **philo, t_resource **rsrc);
void		is_philo_dead(t_philo *philo, t_resource *rsrc);
void		*philo_work(void *argv);
int			start_philo(t_philo *philo, t_resource *rsrc);

void		join_pthread(t_philo *philo);
int			destroy_mutex(t_resource *rsrc, int last);
int			detach_pthread(t_philo *philo, int last);
void		free_rsrc(t_resource *rsrc);

int			ft_atoi(const char *str);

void		spend_time(t_resource *rsrc, long long time_to_spend);
long long	get_now(void);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			p_err(char *str, int code);
#endif