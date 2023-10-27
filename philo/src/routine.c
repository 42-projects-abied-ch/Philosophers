/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:13:51 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 14:48:34 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*Calculate elapsed time since start time, check for stop signal
and print status with philo ID*/
void	print_status(char *str, t_data *data)
{
	long int		time;

	time = -1;
	time = get_time() - data->args->start_time;
	if (time >= 0 && time <= 2147483647 && !check_pulse(data, 0))
	{
		printf("%ld ", time);
		printf("Philosopher %d %s", data->id, str);
	}
}

/*Lock the print mutex to ensure thread safety during printing.
Print status for sleeping, release mutex, sleeps & prints status for thinking*/
void	sleep_think(t_data *data)
{
	pthread_mutex_lock(&data->args->write_mutex);
	print_status("is sleeping💤\n", data);
	pthread_mutex_unlock(&data->args->write_mutex);
	usleepingood(data->args->time_to_sleep);
	pthread_mutex_lock(&data->args->write_mutex);
	print_status("is thinking💡\n", data);
	pthread_mutex_unlock(&data->args->write_mutex);
}

/*Routine of the philosopher
Lock left fork, print status for taking fork
If right fork is not available, sleep and come back to it, 
otherwise lock the right fork, print status for taking fork
and eat.
Record eating time, releases locks, sleep for eating time & unlock forks*/
void	routine(t_data *data)
{
	pthread_mutex_lock(&data->left_fork);
	pthread_mutex_lock(&data->args->write_mutex);
	print_status("has taken a fork🍴\n", data);
	pthread_mutex_unlock(&data->args->write_mutex);
	if (!data->right_fork)
	{
		usleepingood(data->args->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(&data->args->write_mutex);
	print_status("has taken a fork🍴\n", data);
	pthread_mutex_unlock(&data->args->write_mutex);
	pthread_mutex_lock(&data->args->write_mutex);
	print_status("is eating🍽️\n", data);
	pthread_mutex_lock(&data->args->eat);
	data->last_eaten = get_time();
	pthread_mutex_unlock(&data->args->eat);
	pthread_mutex_unlock(&data->args->write_mutex);
	usleepingood(data->args->time_to_eat);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(&data->left_fork);
	sleep_think(data);
}
