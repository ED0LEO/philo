/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlothair <mlothair@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:18:38 by mlothair          #+#    #+#             */
/*   Updated: 2021/12/03 15:33:06 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	main(int argc, char **argv)
{
	t_inits	init;
	t_lock	death;
	t_phil	*phils;
	t_lock	*forks;

	if ((argc < 5 || argc > 6) && error_exit(0, 0))
		return (1);
	memset(&init, 0, sizeof(t_inits));
	memset(&death, 0, sizeof(t_lock));
	if (!init_args(argc, argv, &init) && error_exit(0, 0))
		return (1);
	if (init.number_of_eats == 0)
		return (0);
	phils = malloc(sizeof (t_phil) * init.philosophers);
	if (!phils && error_exit(&phils, 0))
		return (1);
	forks = malloc(sizeof (t_lock) * init.philosophers);
	if (!forks && error_exit(&phils, &forks))
		return (1);
	if (!init_locks(&init, &death, forks) && error_exit(&phils, &forks))
		return (1);
	init_phils(phils, forks, death, &init);
	if (!start(phils, init.philosophers) && error_exit(&phils, &forks))
		return (1);
	return (clean(phils, forks, init.philosophers));
}
