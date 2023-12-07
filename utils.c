/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 12:13:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/03 18:48:24 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	ft_atoi(char *str)
{
	long int	res;

	res = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res >= INT_MAX)
		{
			res = INT_MAX;
			break ;
		}
		++str;
	}
	return ((int)res);
}

long	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	ft_usleep(int todo)
{
	long int	time;

	time = gettime();
	while (gettime() - time < todo)
		usleep(250);
}

void	print_action(t_philo *philo, char *message)
{
	pthread_mutex_lock(&(philo->rules->write));
	if (!is_dead(philo, 0))
		printf("%ld %i %s\n", gettime() - philo->rules->starttime, philo->id,
			message);
	pthread_mutex_unlock(&(philo->rules->write));
}
