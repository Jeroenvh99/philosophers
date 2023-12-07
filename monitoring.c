/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 10:43:43 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 14:06:10 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->eat);
	pthread_mutex_lock(&philo->rules->stop);
	if (!is_dead(philo, 0) && gettime()
		- philo->last_meal >= (long)(philo->rules->t_die))
	{
		pthread_mutex_unlock(&philo->rules->eat);
		pthread_mutex_unlock(&philo->rules->stop);
		if (philo->n_eat != 0)
			print_action(philo, "died");
		is_dead(philo, 1);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->eat);
	pthread_mutex_unlock(&philo->rules->stop);
	return (0);
}

void	monitoring(t_philo *philo)
{
	int		i;

	i = 0;
	while (!is_dead(philo, 0) && i < philo->rules->n_philos)
	{
		if (check_death(&philo[i]))
			return ;
		if (i == philo->rules->n_philos - 1)
			i = 0;
		else
			++i;
	}
	return ;
}
