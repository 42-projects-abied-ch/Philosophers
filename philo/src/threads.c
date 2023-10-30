/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:13:41 by arthur            #+#    #+#             */
/*   Updated: 2023/10/30 18:07:20 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*one_isdead(void *data)
{
	t_dump	*dump;

	dump = (t_dump *)data;
	printf("1\t1 has taken a fork\n");
	usleepingood(dump->args.time_to_die);
	printf("%d\t1 died\n", dump->args.time_to_die + 1);
	return (NULL);
}

void	one_philo(t_dump *dump)
{
	pthread_create(&dump->data->thread_death_id, NULL,
		one_isdead, (void *)dump);
	pthread_join(dump->data->thread_death_id, NULL);
}

/*Executed by a separate thread to monitor the time_to_die condition
of each philosopher
Sleep for time_to_die + 1, so we know that if the philo did not 
eat within this time frame, it is dead. Prevents false positives, eg
a philo being pronounced dead due to timing discrepancies.*/
void	*is_dead(void	*data)
{
	t_data	*philo;

	philo = (t_data *)data;
	usleepingood(philo->args->time_to_die + 1);
	pthread_mutex_lock(&philo->args->eat);
	pthread_mutex_lock(&philo->args->done);
	if (!check_pulse(philo, 0) && !philo->done && ((get_time() - \
		philo->last_eaten) >= (long)(philo->args->time_to_die)))
	{
		pthread_mutex_unlock(&philo->args->eat);
		pthread_mutex_unlock(&philo->args->done);
		pthread_mutex_lock(&philo->args->write_mutex);
		print_status("died\n", philo);
		pthread_mutex_unlock(&philo->args->write_mutex);
		check_pulse(philo, 1);
		pthread_mutex_lock(&philo->args->eat);
		pthread_mutex_lock(&philo->args->done);
	}
	pthread_mutex_unlock(&philo->args->eat);
	pthread_mutex_unlock(&philo->args->done);
	return (NULL);
}

/*If philo ID is even, sleep for a fraction of the eating time to
avoid starting at the same time
Enter a loop until one philosopher dies
Create a new thread to perform the is_dead check concurrently,
call routine and detach the thread.
If the philosopher has eaten enough times, mark aas doneed and increment
done_eating_counter by 1 & check if all philos are done eating
If everyone is done eating, unlock done mutex and send stop signal*/
void	*thread(void *data)
{
	t_data					*ph;

	ph = (t_data *)data;
	if (ph->id % 2 == 0)
		usleepingood(ph->args->time_to_eat / 10);
	while (!check_pulse(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		routine(ph);
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->meals_eaten == ph->args->meals && !ph->args->stop)
		{
			pthread_mutex_lock(&ph->args->done);
			ph->done = 1;
			ph->args->done_eating_counter++;
			if (ph->args->done_eating_counter == ph->args->philo_count)
			{
				pthread_mutex_unlock(&ph->args->done);
				check_pulse(ph, 2);
				return (NULL);
			}
			return (pthread_mutex_unlock(&ph->args->done), NULL);
		}
	}
	return (NULL);
}

/*Iterate over all philosophers
Assign dump->args (shared struct) to the args field of each
struct array index so every thread can access it
Create a new thread for each philosopher, pass the routine function
Continue until all philos are initialized and threads are created*/
int	spiderweb(t_dump *dump)
{
	int	i;

	i = 0;
	if (dump->args.philo_count == 1)
		return (one_philo(dump), 0);
	while (i < dump->args.philo_count)
	{
		dump->data[i].args = &dump->args;
		if (pthread_create(&dump->data[i].thread_id, NULL, thread,
				&dump->data[i]) != 0)
			return (gtfo("pthread failed\n"));
		i++;
	}
	return (1);
}
