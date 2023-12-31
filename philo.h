/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:49:08 by htouil            #+#    #+#             */
/*   Updated: 2023/08/29 15:36:59 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int				n_philos;
	int				t_todie;
	int				t_toeat;
	int				t_tosleep;
	int				n_ofmeals;
	int				*full_philos;
	int				kill;
	pthread_mutex_t	var;
}		t_args;

typedef struct s_philo
{
	int				id;
	int				count_meals;
	pthread_t		philo;
	pthread_mutex_t	fst_fork;
	pthread_mutex_t	*scd_fork;
	long long		st;
	long long		lt;
	t_args			*args;
}		t_philo;

//libft functions:
void		ft_bzero(void *ptr, size_t n);
int			ft_atoi(char *str);

//philo functions;
long long	get_time(void);
void		custom_usleep(t_philo *philo, int t_to);
void		*routine(void *ptr);
void		monitoring(t_args *args, t_philo *philo);
void		print_msg(t_philo *philo, char *msg);

#endif