/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/11/29 19:26:06 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	phil_sleep(long finish)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	while (time_to_mlsec(current_time) < finish)
	{
		usleep(250);
		gettimeofday(&current_time, NULL);
	}
}

t_bool	start(t_phil *phils, int amount)
{
	int				i;
	t_monitoring	monitor;

	i = 0;
	monitor.phils = phils;
	monitor.amount = amount;
	monitor.death = phils[0].death;
	pthread_create(&monitor.thread, NULL,
		   (void *(*)(void *)) monitoring, &monitor);
	while (i < amount)
	{
		if (pthread_create(&(phils[i].thread), NULL,
				(void *(*)(void *)) phil_life, &phils[i]) != 0)
			return (0);
		pthread_detach(phils[i].thread);
		i++;
	}
	usleep(200);
	if (cmp_cont(phils->death, 1))
		return (1);
	pthread_join(monitor.thread, NULL);
	pthread_detach(monitor.thread);
	return (1);
}
