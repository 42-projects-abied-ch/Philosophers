/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:36:22 by arthur            #+#    #+#             */
/*   Updated: 2023/10/28 11:48:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	gtfo(char *str)
{
	ft_putstr_fd("\x1b[31m\033[1merror: \x1b[0m", 2);
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
}

int	main(int argc, char **argv)
{
	t_dump		dump;

	if (!(get_input(argc, argv, &dump)))
		return (gtfo("bad input\n"));
	if (!store_args(&dump) || !spiderweb(&dump))
		return (0);
	stop(&dump);
}
