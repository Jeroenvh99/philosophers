/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 12:19:51 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 12:42:02 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->rules->check_dead);
	if (nb)
		philo->rules->dead = 1;
	if (philo->rules->dead)
	{
		pthread_mutex_unlock(&philo->rules->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->check_dead);
	return (0);
}

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print_action(philo, "has taken a fork");
	if (philo->rules->n_philos == 1)
	{
		ft_usleep(philo->rules->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	print_action(philo, "has taken a fork");
}

static void	philo_eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&(philo->rules->eat));
	philo->last_meal = gettime();
	--(philo->n_eat);
	pthread_mutex_unlock(&(philo->rules->eat));
	ft_usleep(philo->rules->t_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&(philo->fork_l));
	if (is_dead(philo, 0))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->rules->t_sleep);
	if (is_dead(philo, 0))
		return ;
	print_action(philo, "is thinking");
}

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->id % 2 == 0)
		ft_usleep(10); // philos eten in paren, voorkomen dat ze allemaal een vork hebben en niet verder komen
	while (!is_dead(philo, 0) && philo->n_eat != 0)
	{
		take_fork(philo);
		philo_eat(philo);
	}
	return (NULL);
}
