/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/22 20:38:15 by htouil           ###   ########.fr       */
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
	int			i;
	long long	time;

	while (1)
	{
		i = 0;
		while (i < args->n_philos)
		{
			// pthread_mutex_lock(&philo.args.time);
			time = get_time() - philo[i].lt;
			// pthread_mutex_unlock(&philo.args.time);
			if (time >= args->t_todie)
			{
				// pthread_mutex_lock(&philo.args.msg);
				// pthread_mutex_unlock(&philo.args.msg);
				// pthread_mutex_lock(&philo.args.msg);
				printf("%lld %d died\n", get_time() - philo->st, philo->id);
				philo->args->kill = 1;
				// pthread_mutex_unlock(&philo.args.msg);
				return ;
			}
			// if (philo[i].count_meals >= args.n_ofmeals)
			// 	return ;
			i++;
		}
	}
}

void	print_msg(t_philo *philo, char state, t_args *args)
{
	(void)args;
	if (state == 't' && philo->args->kill == 0)
	{
		// pthread_mutex_lock(&args->msg);
		printf("%lld %d is thinking\n", get_time() - philo->st, philo->id);
		// pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'F' && philo->args->kill == 0)
	{
		pthread_mutex_lock(&philo->fst_fork);
		// pthread_mutex_lock(&args->msg);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
		// pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'f' && philo->args->kill == 0)
	{
		pthread_mutex_lock(philo->scd_fork);
		// pthread_mutex_lock(&args->msg);
		printf("%lld %d has taken a fork\n", get_time() - philo->st, philo->id);
		// pthread_mutex_unlock(&args->msg);
	}
	else if (state == 'e' && philo->args->kill == 0)
	{
		// pthread_mutex_lock(&args->msg);
		printf("%lld %d is eating\n", get_time() - philo->st, philo->id);
		// pthread_mutex_unlock(&args->msg);
		// pthread_mutex_lock(&args->time);
		philo->lt = get_time();
		// pthread_mutex_unlock(&args->time);
		philo->count_meals++;
		custom_usleep(philo->args->t_toeat);
		pthread_mutex_unlock(&philo->fst_fork);
		pthread_mutex_unlock(philo->scd_fork);
	}
	else if (state == 's' && philo->args->kill == 0
		&& philo->count_meals < philo->args->n_ofmeals)
	{
		// pthread_mutex_lock(&args->msg);
		printf("%lld %d is sleeping\n", get_time() - philo->st, philo->id);
		// pthread_mutex_unlock(&args->msg);
		custom_usleep(philo->args->t_tosleep);
	}
}

void	*routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (1)
	{
		if (ph->args->kill == 1)
			break ;
		print_msg(ph, 't', ph->args);
		print_msg(ph, 'F', ph->args);
		print_msg(ph, 'f', ph->args);
		print_msg(ph, 'e', ph->args);
		print_msg(ph, 's', ph->args);
		if ((ph->args->n_ofmeals != -1 && ph->count_meals >= ph->args->n_ofmeals)
			|| ph->args->kill == 1)
		{
			// pthread_mutex_lock(&ph.args.satiation);
			// printf("before full philos : %d/%d\n", ph.args.full_philos, ph.args.n_philos);
			// ph.args.full_philos++;
			// printf("after full philos : %d/%d\n", ph.args.full_philos, ph.args.n_philos);
			// pthread_mutex_unlock(&ph.args.satiation);
			break ;
		}
	}
	return (NULL);
}
