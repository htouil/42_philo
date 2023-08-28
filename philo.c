/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:44:09 by htouil            #+#    #+#             */
/*   Updated: 2023/08/27 16:48:56 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][j + 1] == '+')
			j++;
		while (av[i][++j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				exit(1);
		}
	}
}

void	init_args(int ac, char **av, t_args *args, int *full_meals)
{
	check_args(ac, av);
	args->n_philos = ft_atoi(av[1]);
	args->t_todie = ft_atoi(av[2]);
	args->t_toeat = ft_atoi(av[3]);
	args->t_tosleep = ft_atoi(av[4]);
	args->n_ofmeals = -1;
	args->kill = 0;
	args->full_philos = full_meals;
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

	pthread_mutex_init(&args->var, NULL);
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
		philo[i].args = args;
		i++;
	}
}

void	invite_philosophers(t_args *args, t_philo *philo)
{
	int			i;
	long long	begin;

	begin = get_time();
	i = -1;
	while (++i < args->n_philos)
	{
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		pthread_mutex_lock(&args->var);
		philo[i].st = begin;
		philo[i].lt = begin;
		pthread_mutex_unlock(&args->var);
		usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_args		args;
	t_philo		*philo;
	int			i;
	int			full_meals;

	if (ac < 5 || ac > 6)
		return (1);
	full_meals = 1;
	init_args(ac, av, &args, &full_meals);
	philo = (t_philo *)malloc(args.n_philos * sizeof(t_philo));
	if (!philo)
		return (1);
	set_up_table(&args, philo);
	invite_philosophers(&args, philo);
	monitoring(&args, philo);
	i = 0;
	while (i < args.n_philos)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	free(philo);
}
