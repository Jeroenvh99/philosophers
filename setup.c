/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 12:25:07 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 13:04:04 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_isposnum(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9') || *str == '-')
			return (0);
		++str;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (argv[i] && ft_isposnum(argv[i]))
			++i;
		if (i == argc)
			return (1);
		else
			write(2, "incorrect formatting", 20);
	}
	if (argc < 5)
		write(2, "too little arguments", 20);
	if (argc > 6)
		write(2, "too many arguments", 18);
	write(2, ", use\n./philo number_of_philosophers "
		"time_to_die time_to_eat time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]\n",
		119);
	return (0);
}

static void	init_mutex(t_rules *rules)
{
	pthread_mutex_init(&rules->eat, NULL);
	pthread_mutex_init(&rules->stop, NULL);
	pthread_mutex_init(&rules->write, NULL);
	pthread_mutex_init(&rules->check_dead, NULL);
}

static int	init_vars(t_rules *rules, int argc, char **argv)
{
	rules->n_philos = ft_atoi(argv[1]);
	if (rules->n_philos == 0)
		return (0);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	if (rules->t_eat == 0)
		return (0);
	rules->t_sleep = ft_atoi(argv[4]);
	if (rules->t_sleep == 0)
		return (0);
	if (argc == 6)
		rules->n_meals = ft_atoi(argv[5]);
	else
		rules->n_meals = -1;
	return (1);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	if (!init_vars(rules, argc, argv))
	{
		free(rules);
		return (NULL);
	}
	rules->dead = 0;
	rules->philo = (t_philo *)malloc(rules->n_philos * sizeof(t_philo));
	if (!rules->philo)
	{
		free(rules);
		return (NULL);
	}
	init_mutex(rules);
	return (rules);
}
