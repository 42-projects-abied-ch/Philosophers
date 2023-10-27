/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:36:22 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 03:04:19 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	gtfo(char *str)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_pulse2(t_dump *dump)
{
	pthread_mutex_lock(&dump->args.dead);
	if (dump->args.stop)
	{
		pthread_mutex_unlock(&dump->args.dead);
		return (1);
	}
	pthread_mutex_unlock(&dump->args.dead);
	return (0);
}

void	stop(t_dump *dump)
{
	int	i;

	i = -1;
	while (!check_pulse2(dump))
		usleepingood(1);
	while (++i < dump->args.philo_count)
		pthread_join(dump->data[i].thread_id, NULL);
	pthread_mutex_destroy(&dump->args.write_mutex);
	i = -1;
	while (++i < dump->args.philo_count)
		pthread_mutex_destroy(&dump->data[i].left_fork);
	if (dump->args.stop == 2)
		printf("Each philosopher ate %d time(s)\n", dump->args.meals);
	free(dump->data);
}

int	main(int argc, char **argv)
{
	t_dump		dump;

	if (!(get_input(argc, argv, &dump)))
		return (gtfo("bad input\n"));
	dump.data = malloc(dump.args.philo_count * sizeof(t_data));
	if (!dump.data)
		return (gtfo("malloc failed\n"));
	if (!store_args(&dump) || !spiderweb(&dump))
	{
		free(dump.data);
		return (0);
	}
	stop(&dump);
}
