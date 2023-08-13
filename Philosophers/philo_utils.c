/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/13 16:56:54 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(void)
{
	struct timeval		time;
	unsigned long long	secs;
	unsigned long long	usecs;

	gettimeofday(&time, NULL);
	secs = (unsigned long long)time.tv_sec;
	usecs = (unsigned long long)time.tv_usec;
	return ((secs * 1000) + (usecs / 1000));
}

void	custom_usleep(int t_to)
{
	unsigned long long	start;

	start = gettime();
	while (gettime() - start < t_to)
		usleep(85);
}

void	routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	ph->kill = false;
	ph->full_philos = 0;
	ph->count_meals = 0;
	while (1)
	{
		if ((ph->args.n_ofmeals != -1 && ph->count_meals >= ph->args.n_ofmeals)
			|| ph->kill == true)
		{
			ph->full_philos++;
			break ;
		}
		ft_printf("%llu %d is thinking\n", gettime() - ph->st, ph->id);
		pthread_mutex_lock(&ph->fst_fork);
		ft_printf("%llu %d has taken a fork\n", gettime() - ph->st, ph->id);
		pthread_mutex_lock(ph->scd_fork);
		ft_printf("%llu %d has taken a fork\n", gettime() - ph->st, ph->id);
		ft_printf("%llu %d is eating\n", gettime() - ph->st, ph->id);
		ph->lt = gettime();
		ph->count_meals++;
		custom_usleep(ph->args.t_toeat);
		pthread_mutex_unlock(&ph->fst_fork);
		pthread_mutex_unlock(ph->scd_fork);
		ft_printf("%llu %d is sleeping\n", gettime() - ph->st, ph->id);
		custom_usleep(ph->args.t_tosleep);
	}
	return (NULL);
}
