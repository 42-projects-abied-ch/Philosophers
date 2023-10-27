/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:17:38 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 14:51:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libraries.h"

typedef struct s_args
{
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	long int				start_time;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			eat;
	pthread_mutex_t			done;
	int						done_eating_counter;
	int						stop;
}							t_args;

typedef struct s_data
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_args					*args;
	long int				last_eaten;
	unsigned int			meals_eaten;
	int						done;
}	t_data;

typedef struct s_dump
{
	t_data					*data;
	t_args					args;
}	t_dump;

#endif