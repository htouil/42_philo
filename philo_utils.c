/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/21 17:44:47 by htouil           ###   ########.fr       */
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
		if (args->full_philos == args->n_philos)
			return ;
		i = 0;
		while (i < args->n_philos)
		{
			if (philo[i].count_meals < args->n_ofmeals
				&& get_time() - philo[i].lt >= args->t_todie)
			{
				pthread_mutex_lock(&args->msg);
				printf("%lld %d died\n", get_time() - philo->st, philo->id);
				args->kill = 1;
				return ;
			}
			// printf ("full : %d n : %d\n", philo[i].count_meals, args->n_ofmeals);
			if (philo[i].count_meals >= args->n_ofmeals)
				return ;
			i++;
			if (i == args->n_philos - 1)
				i = 0;
		}
	}
}

void	print_msg(t_philo *philo, char state, t_args *args)
{
	// pthread_mutex_lock(&args->msg);
	if (state == 't' && args->kill == 0)
	{
		pthread_mutex_lock(&args->msg);
		printf("%lld %d is thinking\n", get_time() - philo->st, philo->id);
		pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'F' && args->kill == 0)
	{
		pthread_mutex_lock(&philo->fst_fork);
		pthread_mutex_lock(&args->msg);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
		pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'f' && args->kill == 0)
	{
		pthread_mutex_lock(philo->scd_fork);
		pthread_mutex_lock(&args->msg);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
		pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'e' && args->kill == 0)
	{
		pthread_mutex_lock(&args->msg);
		printf("%lld %d is eating\n", get_time() - philo->st, philo->id);
		pthread_mutex_unlock(&args->msg);
		pthread_mutex_lock(&args->time);
		philo->lt = get_time();
		pthread_mutex_unlock(&args->time);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->fst_fork);
		pthread_mutex_unlock(philo->scd_fork);
		custom_usleep(philo->args.t_toeat);
	}
	else if (state == 's' && args->kill == 0)
	{
		pthread_mutex_lock(&args->msg);
		printf("%lld %d is sleeping\n", get_time() - philo->st, philo->id);
		pthread_mutex_unlock(&args->msg);
		custom_usleep(philo->args.t_tosleep);
	}
	// pthread_mutex_unlock(&args->msg);
}

void	*routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (1)
	{
		// printf("%lld %d is thinking\n", get_time() - ph->st, ph->id);
		// pthread_mutex_lock(&ph->fst_fork);
		// printf("%lld %d has taken a fork\n", get_time() - ph->st, ph->id);
		// pthread_mutex_lock(ph->scd_fork);
		// printf("%lld %d has taken a fork\n", get_time() - ph->st, ph->id);
		// printf("%lld %d is eating\n", get_time() - ph->st, ph->id);
		// ph->lt = get_time();
		// ph->count_meals++;
		// custom_usleep(ph->args.t_toeat);
		// pthread_mutex_unlock(&ph->fst_fork);
		// pthread_mutex_unlock(ph->scd_fork);
		// printf("%lld %d is sleeping\n", get_time() - ph->st, ph->id);
		// custom_usleep(ph->args.t_tosleep);
		if ((ph->args.n_ofmeals != -1 && ph->count_meals == ph->args.n_ofmeals)
			|| ph->args.kill == 1)
		{
			pthread_mutex_lock(&ph->args.satiation);
			ph->args.full_philos++;
			pthread_mutex_unlock(&ph->args.satiation);
			break ;
		}
		print_msg(ph, 't', &ph->args);
		print_msg(ph, 'F', &ph->args);
		print_msg(ph, 'f', &ph->args);
		print_msg(ph, 'e', &ph->args);
		if (ph->args.full_philos == ph->args.n_philos)
			print_msg(ph, 's', &ph->args);
	}
	return (NULL);
}
