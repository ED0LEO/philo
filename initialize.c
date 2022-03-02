/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 15:35:27 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	init_phils(t_phil *phils, t_lock *forks, t_lock death, t_inits *init)
{
	int	i;

	i = 0;
	while (i < init->philosophers)
	{
		memset(&phils[i], 0, sizeof(t_phil));
		(phils)[i].writing = &init->writing;
		(phils)[i].eating_time = init->time_to_eat;
		(phils)[i].sleep_time = init->time_to_sleep;
		(phils)[i].eats_needed = init->number_of_eats;
		(phils)[i].starving = init->time_to_die;
		(phils)[i].odd_turn = &init->odd_turn;
		(phils)[i].number = i + 1;
		(phils)[i].death = &death;
		(phils)[i].left_fork = &forks[i];
		if (init->philosophers == 1)
			(phils)[i].right_fork = 0;
		else if (i == init->philosophers - 1)
			(phils)[i].right_fork = &forks[0];
		else
			(phils)[i].right_fork = &forks[i + 1];
		i++;
	}
}

t_bool	init_locks(t_inits	*init, t_lock *death, t_lock *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&init->odd_turn.lock, NULL) != 0)
		return (0);
	if (init->philosophers % 2 == 0)
		cng_cont(&init->odd_turn, 1);
	else
		cng_cont(&init->odd_turn, 0);
	if (pthread_mutex_init(&(death->lock), NULL) != 0)
		return (0);
	cng_cont(death, 0);
	if (pthread_mutex_init(&(init->writing.lock), NULL) != 0)
		return (0);
	cng_cont(&init->writing, 0);
	while (i < init->philosophers)
	{
		memset(&forks[i], 0, sizeof(t_lock));
		if (pthread_mutex_init(&(forks[i].lock), NULL) != 0)
			return (0);
		cng_cont(&forks[i], 1);
		i++;
	}
	return (1);
}

t_bool	init_args(int argc, char **argv, t_inits *init)
{
	init->philosophers = ft_atoi(argv[1]);
	init->time_to_die = ft_atoi(argv[2]);
	init->time_to_eat = ft_atoi(argv[3]);
	init->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		init->number_of_eats = ft_atoi(argv[5]);
	else
		init->number_of_eats = -1;
	if (init->philosophers <= 0
		|| init->time_to_die < 0
		|| init->time_to_eat < 0
		|| init->time_to_sleep < 0
		|| (init->number_of_eats < 0 && argc == 6))
		return (0);
	return (1);
}
