/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 15:27:24 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

t_bool	error_exit(t_phil **phils, t_lock **forks)
{
	if (phils)
		free(phils);
	if (forks)
		free(forks);
	write(2, "Error\n", 6);
	return (1);
}

t_bool	clean(t_phil *phils, t_lock *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&phils->death->lock);
	pthread_mutex_destroy(&phils->writing->lock);
	pthread_mutex_destroy(&phils->odd_turn->lock);
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&phils[i].left_fork->lock);
		i++;
	}
	if (phils)
		free(phils);
	if (forks)
		free(forks);
	return (0);
}
