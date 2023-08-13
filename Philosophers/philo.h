/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:49:08 by htouil            #+#    #+#             */
/*   Updated: 2023/08/13 16:49:53 by htouil           ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_args
{
	int	n_philos;
	int	t_todie;
	int	t_toeat;
	int	t_tosleep;
	int	n_ofmeals;
}		t_args;

typedef struct s_philo
{
	int						id;
	pthread_t				philo;
	pthread_mutex_t			fst_fork;
	pthread_mutex_t			*scd_fork;
	int						count_meals;
	int						full_philos;
	unsigned long long		st;
	unsigned long long		lt;
	bool					kill;
	t_args					args;
}		t_philo;

//libft functions:
void				ft_bzero(void *ptr, size_t n);
int					ft_atoi(char *str);

//philo functions;
void				routine(void *ptr);

#endif