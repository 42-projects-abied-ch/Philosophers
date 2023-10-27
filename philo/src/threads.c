#include "../include/philosophers.h"

void	*is_dead(void	*data)
{
	t_data					*ph;

	ph = (t_data *)data;
	usleepingood(ph->pa->time_to_die + 1);
	pthread_mutex_lock(&ph->pa->time_eat);
	pthread_mutex_lock(&ph->pa->finish);
	if (!check_pulse(ph, 0) && !ph->finish && ((get_time() - ph->ms_eat) \
		>= (long)(ph->pa->time_to_die)))
	{
		pthread_mutex_unlock(&ph->pa->time_eat);
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_lock(&ph->pa->write_mutex);
		print_status("died🪦\n", ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		check_pulse(ph, 1);
	}
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_data					*ph;

	ph = (t_data *)data;
	if (ph->id % 2 == 0)
		usleepingood(ph->pa->time_to_eat / 10);
	while (!check_pulse(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		routine(ph);
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->nb_eat == ph->pa->m_eat)
		{
			pthread_mutex_lock(&ph->pa->finish);
			ph->finish = 1;
			ph->pa->nb_p_finish++;
			if (ph->pa->nb_p_finish == ph->pa->philo_count)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_pulse(ph, 2);
			}
			pthread_mutex_unlock(&ph->pa->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	spiderweb(t_dump *dump)
{
	int	i;

	i = 0;
	while (i < dump->args.philo_count)
	{
		dump->data[i].pa = &dump->args;
		if (pthread_create(&dump->data[i].thread_id, NULL, thread, &dump->data[i]) != 0)
			return (gtfo("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}
