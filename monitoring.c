/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/11/29 05:20:00 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

t_bool	all_turn_eated(t_phil *phils, int num_of_phils, t_eat_turn *turn)
{
	int	i;

	i = 0;
	while (i < num_of_phils)
	{
		if (!turn->odd_turn && (i + 1) % 2 == 0)
		{
			if (phils[i].eat_times != turn->eat_even + 1)
				return (0);
		}
		if (turn->odd_turn && (i + 1) % 2 != 0)
		{
			if (phils[i].eat_times != turn->eat_odd + 1)
				return (0);
		}
		i++;
	}
	if (turn->odd_turn)
		turn->eat_odd++;
	else
		turn->eat_even++;
	return (1);
}

void	*monitoring(t_monitoring	*monitor)
{
	t_eat_turn	turn;

	memset(&turn, 0, sizeof (t_eat_turn));
	if (cmp_cont(monitor->death, 0) && monitor->amount % 2 == 0)
		turn.odd_turn = 1;
	while (1)
	{
		usleep(250);
		if (cmp_cont(monitor->death, 1))
			return (0);
		turn.ret = all_turn_eated(monitor->phils, monitor->amount, &turn);
		if (turn.ret && (cmp_cont(monitor->phils[0].odd_turn, 1)))
		{
			cng_cont(monitor->phils[0].odd_turn, 0);
			turn.odd_turn = 0;
		}
		else if (turn.ret)
		{
			cng_cont(monitor->phils[0].odd_turn, 1);
			turn.odd_turn = 1;
		}
		if ((monitor->phils[0].eats_needed >= 0)
			 && eated_equal(monitor->phils, monitor->amount))
			return (0);
	}
}

t_bool	eated_equal(t_phil *phils, int num_of_phils)
{
	int	i;

	i = 0;
	while (i < num_of_phils)
	{
		if (phils[i].eats_needed != phils[i].eat_times)
			return (0);
		i++;
	}
	return (1);
}
