/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:14:03 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 02:43:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*Check for a stop signal:
-Lock the 'dead' mutex to ensure that no other thread accesses
it.
-If i != 0, set the 'stop' flag
-Check if the 'stop' flag is set, unlock the mutex and return 1/0*/
int	check_pulse(t_data *ph, int i)
{
	pthread_mutex_lock(&ph->args->dead);
	if (i)
		ph->args->stop = i;
	if (ph->args->stop)
	{
		pthread_mutex_unlock(&ph->args->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->args->dead);
	return (0);
}

long	get_time(void)
{
	long			time;
	struct timeval	tv;

	time = 0;
	if (gettimeofday(&tv, NULL) == -1)
		gtfo("could not get time of day\n");
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

/*Better version of usleep, since it is not very precise*/
void	usleepingood(long int time_in_ms)
{
	long	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
