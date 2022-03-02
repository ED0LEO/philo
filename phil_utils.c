/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:56:58 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 16:14:29 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

long	time_to_mlsec(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_phil *phil, char *status, long time)
{
	pthread_mutex_lock(&phil->writing->lock);
	printf("%.13ld %d %s\n", time - phil->starting_time, phil->number, status);
	if (cmp_cont(phil->death, 0))
		pthread_mutex_unlock(&phil->writing->lock);
}

t_bool	cmp_cont(t_lock *obj, t_bool checker)
{
	t_bool	ret;

	ret = 0;
	pthread_mutex_lock(&obj->lock);
	if (obj->content == checker)
	{
		pthread_mutex_unlock(&obj->lock);
		ret = 1;
	}
	else
		pthread_mutex_unlock(&obj->lock);
	return (ret);
}

void	cng_cont(t_lock *obj, t_bool val)
{
	pthread_mutex_lock(&obj->lock);
	obj->content = val;
	pthread_mutex_unlock(&obj->lock);
}
