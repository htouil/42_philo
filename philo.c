/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:44:09 by htouil            #+#    #+#             */
/*   Updated: 2023/08/18 23:33:48 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(char **av, t_args *args)
{
	args->n_philos = ft_atoi(av[1]);
	args->t_todie = ft_atoi(av[2]);
	args->t_toeat = ft_atoi(av[3]);
	args->t_tosleep = ft_atoi(av[4]);
	args->n_ofmeals = -1;
	args->kill = false;
	if (av[5])
		args->n_ofmeals = ft_atoi(av[5]);
	if (args->n_philos <= 0 || args->n_philos > 200
		|| args->t_todie < 60 || args->t_toeat < 60
		|| args->t_tosleep < 60 || args->n_ofmeals < -1 || args->n_ofmeals == 0)
		exit(1);
}

void	set_up_table(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->n_philos)
	{
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].fst_fork, NULL);
		i++;
	}
	i = 0;
	while (i < args->n_philos)
	{
		philo[i].scd_fork = &philo[(i + 1) % args->n_philos].fst_fork;
		philo[i].args = *args;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_args		args;
	t_philo		*philo;
	long long	begin;
	int			i;

	if (ac < 5 || ac > 6)
		return (1);
	init_args(av, &args);
	philo = (t_philo *)malloc(args.n_philos * sizeof(t_philo));
	if (!philo)
		return (1);
	set_up_table(&args, philo);
	begin = get_time();
	i = 0;
	while (i < args.n_philos)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		philo[i].st = begin;
		philo[i].lt = begin;
		i++;
		usleep(33);
	}
	i = 0;
	while (i < args.n_philos)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	monitoring(&args, philo);
	i = 0;
	while (i < args.n_philos)
	{
		printf("philo %d : %d\n", philo[i].id, philo[i].count_meals);
		i++;
	}
	free(philo);
}
