/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <mlothair@student.21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:15:09 by mlothair          #+#    #+#             */
/*   Updated: 2021/11/26 19:59:11 by mlothair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long			i;
	int							p;
	long int					res;

	i = 0;
	p = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
	}
	if (*str == 45)
		p = -1;
	if (*str == 45 || *str == 43)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		i = ((*str) - 48) + (i * 10);
		if (i > 2147483647 && p == 1)
			return (-1);
		if (i > 2147483648 && p == -1)
			return (-1);
		str++;
	}
	res = p * (int) i;
	return (res);
}
