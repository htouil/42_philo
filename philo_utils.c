/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/15 14:02:15 by htouil           ###   ########.fr       */
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
		usleep(85);
}

void	monitoring(t_args *args, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < args->n_philos)
		{
			if (get_time() - philo[i].lt >= args->t_todie)
			{
				printf("%lld %d died\n", get_time() - philo->st, philo->id);
				philo->args.kill = true;
				return ;
			}
			i++;
		}
		if (philo->args.full_philos == args->n_philos)
			return ;
	}
}

void	print_msg(t_philo *philo, char state)
{
	if (state == 't' && philo->args.kill == false)
		printf("%lld %d is thinking\n", get_time() - philo->st, philo->id);
	else if (state == 'F' && philo->args.kill == false)
	{
		pthread_mutex_lock(&philo->fst_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
	}
	else if (state == 'f' && philo->args.kill == false)
	{
		pthread_mutex_lock(philo->scd_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
	}
	else if (state == 'e' && philo->args.kill == false)
	{
		printf("%lld %d is eating\n", get_time() - philo->st, philo->id);
		philo->lt = get_time();
		philo->count_meals++;
		custom_usleep(philo->args.t_toeat);
		pthread_mutex_unlock(&philo->fst_fork);
		pthread_mutex_unlock(philo->scd_fork);
	}
	else if (state == 's' && philo->args.kill == false)
	{
		printf("%lld %d is sleeping\n", get_time() - philo->st, philo->id);
		custom_usleep(philo->args.t_tosleep);
	}
}

void	*routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (1)
	{
		printf("%lld %d is thinking\n", get_time() - ph->st, ph->id);
		pthread_mutex_lock(&ph->fst_fork);
		printf("%lld %d has taken a fork\n", get_time() - ph->st, ph->id);
		pthread_mutex_lock(ph->scd_fork);
		printf("%lld %d has taken a fork\n", get_time() - ph->st, ph->id);
		printf("%lld %d is eating\n", get_time() - ph->st, ph->id);
		ph->lt = get_time();
		ph->count_meals++;
		custom_usleep(ph->args.t_toeat);
		pthread_mutex_unlock(&ph->fst_fork);
		pthread_mutex_unlock(ph->scd_fork);
		printf("%lld %d is sleeping\n", get_time() - ph->st, ph->id);
		custom_usleep(ph->args.t_tosleep);
		// print_msg(ph, 't');
		// print_msg(ph, 'F');
		// print_msg(ph, 'f');
		// print_msg(ph, 'e');
		// print_msg(ph, 's');
		if ((ph->args.n_ofmeals != -1 && ph->count_meals >= ph->args.n_ofmeals)
			|| ph->args.kill == true)
		{
			ph->args.full_philos++;
			break ;
		}
	}
	return (NULL);
}
