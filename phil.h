/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:13:43 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 15:35:27 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>

typedef unsigned char	t_bool;

typedef struct s_lock
{
	pthread_mutex_t	lock;
	t_bool			content;
}				t_lock;

typedef struct s_eat_turn
{
	t_bool	odd_turn;
	int		eat_odd;
	int		eat_even;
	int		ret;
}				t_eat_turn;

typedef struct s_phil
{
	pthread_t	thread;
	int			number;
	long		last_eat;
	long		eating_time;
	long		starving;
	long		sleep_time;
	int			eats_needed;
	int			eat_times;
	long		starting_time;
	t_bool		holding_left_fork;
	t_bool		holding_right_fork;
	t_lock		*odd_turn;
	t_lock		*death;
	t_lock		*left_fork;
	t_lock		*right_fork;
	t_lock		*writing;
}				t_phil;

typedef struct s_monitoring
{
	t_phil		*phils;
	int			amount;
	pthread_t	thread;
	t_lock		*death;
}				t_monitoring;

typedef struct s_inits
{
	int			philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_eats;
	t_lock		writing;
	t_lock		odd_turn;
}				t_inits;

int		ft_atoi(const char *str);
void	phil_sleep(long finish);
void	*drop_forks(t_phil *phil);
void	take_forks(t_phil *phil);
long	time_to_mlsec(struct timeval time);
void	print_message(t_phil *phil, char *status, long time);
void	cng_cont(t_lock *obj, t_bool val);
t_bool	cmp_cont(t_lock *obj, t_bool checker);
t_bool	eated_equal(t_phil *phils, int num_of_phils);
void	*monitoring(t_monitoring	*monitor);
t_bool	init_args(int argc, char **argv, t_inits *init);
t_bool	clean(t_phil *phils, t_lock *forks, int number_of_philosophers);
void	*phil_life(t_phil *phil);
t_bool	start(t_phil *phils, int amount);
t_bool	error_exit(t_phil **phils, t_lock **forks);
t_bool	init_locks(t_inits	*init, t_lock *death, t_lock *forks);
void	init_phils(t_phil *phils, t_lock *forks, t_lock death, t_inits *init);

#endif
