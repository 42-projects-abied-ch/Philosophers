/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:15:05 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 18:46:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*Initialize mutexes to prevent data races*/
void	mutex(t_dump *dump)
{
	pthread_mutex_init(&dump->args.write_mutex, NULL);
	pthread_mutex_init(&dump->args.dead, NULL);
	pthread_mutex_init(&dump->args.eat, NULL);
	pthread_mutex_init(&dump->args.done, NULL);
}

/*Store arguments in the structs, initialize a mutex for each
philosopher's LEFT fork, the right one is just a pointer to next
philosopher's left fork
Return if only 1 philosopher, since it will automatically starve
due to only having one fork*/
int	store_args(t_dump *dump)
{
	int	i;

	i = -1;
	dump->args.start_time = get_time();
	dump->args.stop = 0;
	dump->args.done_eating_counter = 0;
	mutex(dump);
	while (++i < dump->args.philo_count)
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
	}

	return (1);
}
