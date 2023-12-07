/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 17:04:47 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 13:29:29 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_rules(t_rules *rules, int detach)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		pthread_mutex_destroy(&rules->philo[i].fork_l);
		pthread_mutex_destroy(rules->philo[i].fork_r);
		if (detach)
			pthread_detach(rules->philo[i].thread);
		++i;
	}
	free(rules->philo);
	pthread_mutex_destroy(&rules->stop);
	pthread_mutex_destroy(&rules->eat);
	pthread_mutex_destroy(&rules->check_dead);
	free(rules);
}

static int	init_philo(t_rules *rules, int i)
{
	rules->philo[i].id = i + 1;
	rules->philo[i].last_meal = gettime();
	rules->philo[i].fork_r = NULL;
	rules->philo[i].rules = rules;
	rules->philo[i].n_eat = rules->n_meals;
	if (pthread_mutex_init(&(rules->philo[i].fork_l), NULL) != 0)
		return (0);
	return (1);
}

static int	start_philos(t_rules *rules)
{
	int	i;

	rules->starttime = gettime();
	i = 0;
	while (i < rules->n_philos)
	{
		if (init_philo(rules, i) == 0)
			break ;
		if (i == rules->n_philos - 1)
			rules->philo[i].fork_r = &rules->philo[0].fork_l;
		else
			rules->philo[i].fork_r = &rules->philo[i + 1].fork_l;
		if (pthread_create(&rules->philo[i].thread, NULL, &philo_routine,
				&(rules->philo[i])) != 0)
			break ;
		++i;
	}
	if (i < rules->n_philos)
	{
		rules->n_philos = i;
		return (0);
	}
	monitoring(rules->philo);
	return (1);
}

static int	end_philos(t_rules *rules)
{
	int	i;

	i = rules->n_philos - 1;
	while (i > -1)
	{
		if (pthread_join(rules->philo[i].thread, NULL) != 0)
		{
			rules->n_philos = i + 1;
			return (0);
		}
		--i;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (!check_args(argc, argv))
		return (1);
	rules = init_rules(argc, argv);
	if (!rules)
		return (1);
	if (!start_philos(rules))
	{
		write(2, "thread creation error\n", 22);
		free_rules(rules, 1);
		return (1);
	}
	if (!end_philos(rules))
	{
		write(2, "thread joining error\n", 21);
		free_rules(rules, 1);
		return (1);
	}
	free_rules(rules, 0);
	return (0);
}
