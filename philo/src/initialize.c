/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:14:57 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 14:51:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	mutex(t_dump *dump)
{
	pthread_mutex_init(&dump->args.write_mutex, NULL);
	pthread_mutex_init(&dump->args.dead, NULL);
	pthread_mutex_init(&dump->args.eat, NULL);
	pthread_mutex_init(&dump->args.done, NULL);
}

int	store_args(t_dump *dump)
{
	int	i;

	i = 0;
	dump->args.start_time = get_time();
	dump->args.stop = 0;
	dump->args.done_eating_counter = 0;
	mutex(dump);
	while (i < dump->args.philo_count)
	{
		dump->data[i].id = i + 1;
		dump->data[i].last_eaten = dump->args.start_time;
		dump->data[i].meals_eaten = 0;
		dump->data[i].done = 0;
		dump->data[i].right_fork = NULL;
		pthread_mutex_init(&dump->data[i].left_fork, NULL);
		if (dump->args.philo_count == 1)
			return (1);
		if (i == dump->args.philo_count - 1)
			dump->data[i].right_fork = &dump->data[0].left_fork;
		else
			dump->data[i].right_fork = &dump->data[i + 1].left_fork;
		i++;
	}
	return (1);
}
