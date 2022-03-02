/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 15:36:38 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	*drop_forks(t_phil *phil)
{
	if (phil->holding_left_fork)
	{
		cng_cont(phil->left_fork, 1);
		phil->holding_left_fork = 0;
	}
	if (phil->holding_right_fork)
	{
		cng_cont(phil->right_fork, 1);
		phil->holding_right_fork = 0;
	}
	return (0);
}

void	take_forks(t_phil *phil)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = time_to_mlsec(time);
	if (cmp_cont(phil->left_fork, 1))
	{
		cng_cont(phil->left_fork, 0);
		print_message(phil, "has taken a fork", current_time);
		phil->holding_left_fork = 1;
	}
	if (!phil->right_fork)
		return ;
	if (cmp_cont(phil->right_fork, 1))
	{
		cng_cont(phil->right_fork, 0);
		print_message(phil, "has taken a fork", current_time);
		phil->holding_right_fork = 1;
	}
}
