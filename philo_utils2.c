/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:24:15 by htouil            #+#    #+#             */
/*   Updated: 2023/08/29 15:36:39 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		secs;
	long long		usecs;

	gettimeofday(&time, NULL);
	secs = (long long)time.tv_sec;
	usecs = (long long)time.tv_usec;
	return ((secs * 1000) + (usecs / 1000));
}

void	custom_usleep(t_philo *philo, int t_to)
{
	long long	start;

	start = get_time();
	while (get_time() - start < t_to)
	{
		pthread_mutex_lock(&philo->args->var);
		if (philo->args->kill == 1 || *philo->args->full_philos == 0)
		{
			pthread_mutex_unlock(&philo->args->var);
			break ;
		}
		pthread_mutex_unlock(&philo->args->var);
		usleep(200);
	}
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->var);
	if (philo->args->kill == 0)
		printf("%lld %d %s\n", get_time() - philo->st, philo->id, msg);
	pthread_mutex_unlock(&philo->args->var);
}
