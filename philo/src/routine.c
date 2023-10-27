#include "../include/philosophers.h"

void	print_status(char *str, t_data *data)
{
	long int		time;

	time = -1;
	time = get_time() - data->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_pulse(data, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", data->id, str);
	}
}

void	sleep_think(t_data *data)
{
	pthread_mutex_lock(&data->pa->write_mutex);
	print_status("is sleeping💤\n", data);
	pthread_mutex_unlock(&data->pa->write_mutex);
	usleepingood(data->pa->sleep);
	pthread_mutex_lock(&data->pa->write_mutex);
	print_status("is thinking💡\n", data);
	pthread_mutex_unlock(&data->pa->write_mutex);
}

void	routine(t_data *data)
{
	pthread_mutex_lock(&data->l_f);
	pthread_mutex_lock(&data->pa->write_mutex);
	print_status("has taken a fork🍴\n", data);
	pthread_mutex_unlock(&data->pa->write_mutex);
	if (!data->r_f)
	{
		usleepingood(data->pa->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(data->r_f);
	pthread_mutex_lock(&data->pa->write_mutex);
	print_status("has taken a fork🍴\n", data);
	pthread_mutex_unlock(&data->pa->write_mutex);
	pthread_mutex_lock(&data->pa->write_mutex);
	print_status("is eating🍽️\n", data);
	pthread_mutex_lock(&data->pa->time_eat);
	data->ms_eat = get_time();
	pthread_mutex_unlock(&data->pa->time_eat);
	pthread_mutex_unlock(&data->pa->write_mutex);
	usleepingood(data->pa->time_to_eat);
	pthread_mutex_unlock(data->r_f);
	pthread_mutex_unlock(&data->l_f);
	sleep_think(data);
}
