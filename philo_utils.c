/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/25 00:36:44 by htouil           ###   ########.fr       */
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

void	custom_usleep(int t_to)
{
	long long	start;

	start = get_time();
	while (get_time() - start < t_to)
		usleep(10);
}

void	monitoring(t_args *args, t_philo *philo)
{
	int			i;
	long long	time;

	while (1)
	{
		i = 0;
		while (i < args->n_philos)
		{
			// pthread_mutex_lock(&philo->args->var);
			time = get_time() - philo[i].lt;
			// pthread_mutex_unlock(&philo->args->var);
			if (time >= args->t_todie)
			{
				// pthread_mutex_lock(&philo->args->var);
				philo->args->kill = 1;
				printf("%lld %d died\n", get_time() - philo->st, philo->id);
				// pthread_mutex_unlock(&philo->args->var);
				// pthread_mutex_lock(&philo->args->var);
				// pthread_mutex_unlock(&philo->args->var);
				if (args->n_philos == 1)
					pthread_mutex_unlock(&philo->fst_fork);
				return ;
			}
			i++;
		}
		if (!*philo->args->full_philos)
			return ;
	}
}

void	print_msg(t_philo *philo, char *msg)
{
	if (philo->args->kill == 0)
	{
		pthread_mutex_lock(&philo->args->var);
		printf("%lld %d %s\n", get_time() - philo->st, philo->id, msg);
		pthread_mutex_unlock(&philo->args->var);
	}
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->fst_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->scd_fork);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");
		pthread_mutex_lock(&philo->args->var);
		philo->lt = get_time();
		pthread_mutex_unlock(&philo->args->var);
		philo->count_meals++;
		custom_usleep(philo->args->t_toeat);
		pthread_mutex_unlock(&philo->fst_fork);
		pthread_mutex_unlock(philo->scd_fork);
		print_msg(philo, "is sleeping");
		custom_usleep(philo->args->t_tosleep);
		print_msg(philo, "is thinking");
		if (philo->args->n_ofmeals != -1
			&& philo->count_meals >= philo->args->n_ofmeals)
		{
			pthread_mutex_lock(&philo->args->var);
			*philo->args->full_philos = 0;
			pthread_mutex_unlock(&philo->args->var);
			break ;
		}
		if (philo->args->kill == 1)
			break ;
	}
	return (NULL);
}
