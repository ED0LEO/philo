/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 16:28:12 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	*death(t_phil *phil)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (cmp_cont(phil->death, 0))
	{
		pthread_mutex_lock(&phil->writing->lock);
		cng_cont(phil->death, 1);
		printf("%.13ld %d %s\n",
			   time_to_mlsec(current_time) - phil->starting_time,
			   phil->number, "died");
	}
	return (0);
}

void	*sleeping(t_phil *phil)
{
	struct timeval	current_time;
	long			time_ml;
	long			sleep_end;
	long			death_time;

	gettimeofday(&current_time, NULL);
	time_ml = time_to_mlsec(current_time);
	sleep_end = phil->last_eat + phil->sleep_time + phil->eating_time;
	death_time = phil->last_eat + phil->starving;
	print_message(phil, "is sleeping", time_ml);
	drop_forks(phil);
	if (death_time < sleep_end)
	{
		phil_sleep(death_time);
		return (death(phil));
	}
	else
		phil_sleep(sleep_end);
	return (0);
}

void	*thinking(t_phil *phil)
{
	struct timeval	current_time;
	long			time_ml;
	long			death_time;

	death_time = phil->last_eat + phil->starving;
	gettimeofday(&current_time, NULL);
	time_ml = time_to_mlsec(current_time);
	print_message(phil, "is thinking", time_ml);
	while (time_ml <= death_time)
	{
		if (phil->number % 2 == 0 && cmp_cont(phil->odd_turn, 0))
			take_forks(phil);
		else if (phil->number % 2 != 0 && cmp_cont(phil->odd_turn, 1))
			take_forks(phil);
		else
			usleep(180);
		if (phil->holding_left_fork && phil->holding_right_fork)
			return (0);
		gettimeofday(&current_time, NULL);
		time_ml = time_to_mlsec(current_time);
	}
	death(phil);
	return (0);
}

void	*eating(t_phil *phil)
{
	struct timeval	current_time;
	long			time_ml;
	long			eat_end;
	long			death_time;

	gettimeofday(&current_time, NULL);
	time_ml = time_to_mlsec(current_time);
	phil->last_eat = time_ml;
	print_message(phil, "is eating", time_ml);
	eat_end = phil->last_eat + phil->eating_time;
	death_time = phil->last_eat + phil->starving;
	phil->eat_times++;
	if (death_time < eat_end)
	{
		phil_sleep(death_time);
		return (death(phil));
	}
	else
		phil_sleep(eat_end);
	return (0);
}

void	*phil_life(t_phil *phil)
{
	struct timeval	current_time;
	int				i;

	i = 0;
	gettimeofday(&current_time, NULL);
	phil->starting_time = time_to_mlsec(current_time);
	phil->last_eat = time_to_mlsec(current_time);
	while (time_to_mlsec(current_time) < phil->last_eat + phil->starving)
	{
		if (i == 3)
			i = 0;
		if (i == 0)
			thinking(phil);
		if (i == 1)
			eating(phil);
		if (i == 2)
			sleeping(phil);
		i++;
		if (cmp_cont(phil->death, 1))
			return (0);
		gettimeofday(&current_time, NULL);
	}
	return (death(phil));
}
