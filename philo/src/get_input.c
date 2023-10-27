/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:56:05 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 02:05:37 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	get_input(int argc, char **argv, t_dump *dump)
{
	if ((argc == 5 || argc == 6) && isnum(argv, 0, 1))
	{
		dump->args.philo_count = ft_atoi(argv[1]);
		dump->args.time_to_die = ft_atoi(argv[2]);
		dump->args.time_to_eat = ft_atoi(argv[3]);
		dump->args.sleep = ft_atoi(argv[4]);
		dump->args.m_eat = -1;
		if (argc == 6)
			dump->args.m_eat = ft_atoi(argv[5]);
		if (dump->args.philo_count <= 0 || dump->args.time_to_die <= 0 || dump->args.time_to_eat <= 0 \
			|| dump->args.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}
