/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 17:53:26 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 13:04:28 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_rules
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				dead;
	long int		starttime;
	pthread_mutex_t	eat;
	pthread_mutex_t	stop;
	pthread_mutex_t	write;
	pthread_mutex_t	check_dead;
	struct s_philo	*philo;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long int		last_meal;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}					t_philo;

int					ft_atoi(char *str);
int					check_args(int argc, char **argv);
t_rules				*init_rules(int argc, char **argv);
long				gettime(void);
void				ft_usleep(int todo);
void				print_action(t_philo *philo, char *message);
int					is_dead(t_philo *philo, int nb);
void				*philo_routine(void *philosopher);
void				monitoring(void *philo);

#endif