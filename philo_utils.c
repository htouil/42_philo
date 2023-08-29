/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:56:16 by htouil            #+#    #+#             */
/*   Updated: 2023/08/29 15:48:24 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring_termination_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->var);
	if (!*philo->args->full_philos)
	{
		pthread_mutex_unlock(&philo->args->var);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->var);
	return (0);
}

void	monitoring(t_args *args, t_philo *philo)
{
	int			i;
	long long	time;

	while (1)
	{
		i = -1;
		while (++i < args->n_philos)
		{
			pthread_mutex_lock(&philo->args->var);
			time = get_time() - philo[i].lt;
			pthread_mutex_unlock(&philo->args->var);
			if (time >= args->t_todie)
			{
				pthread_mutex_lock(&philo->args->var);
				philo->args->kill = 1;
				pthread_mutex_unlock(&philo->args->var);
				printf("%lld %d died\n", get_time() - philo[i].st, philo[i].id);
				if (args->n_philos == 1)
					pthread_mutex_unlock(&philo->fst_fork);
				return ;
			}
		}
		if (monitoring_termination_check(philo) == 1)
			return ;
	}
}

int	routine_termination_check(t_philo *philo)
{
	if (philo->args->n_ofmeals != -1
		&& philo->count_meals >= philo->args->n_ofmeals)
	{
		pthread_mutex_lock(&philo->args->var);
		*philo->args->full_philos = 0;
		pthread_mutex_unlock(&philo->args->var);
		return (1);
	}
	pthread_mutex_lock(&philo->args->var);
	if (philo->args->kill == 1)
	{
		pthread_mutex_unlock(&philo->args->var);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->var);
	return (0);
}

void	eating_msgs(t_philo *philo)
{
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print_msg(philo, "is thinking");
		pthread_mutex_lock(&philo->fst_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->scd_fork);
		eating_msgs(philo);
		pthread_mutex_lock(&philo->args->var);
		philo->lt = get_time();
		pthread_mutex_unlock(&philo->args->var);
		philo->count_meals++;
		custom_usleep(philo, philo->args->t_toeat);
		pthread_mutex_unlock(&philo->fst_fork);
		pthread_mutex_unlock(philo->scd_fork);
		print_msg(philo, "is sleeping");
		custom_usleep(philo, philo->args->t_tosleep);
		if (routine_termination_check(philo) == 1)
			break ;
	}
	return (NULL);
}
