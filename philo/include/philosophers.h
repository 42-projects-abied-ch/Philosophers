#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/*
** structures
*/

typedef struct s_args
{
	int						philo_count;
	int						time_to_die;
	int						time_to_eat;
	int						sleep;
	int						m_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_p_finish;
	int						stop;
}							t_args;

typedef struct s_data
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*r_f;
	pthread_mutex_t			l_f;
	t_args					*pa;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}	t_data;

typedef struct s_dump
{
	t_data					*data;
	t_args					args;
}	t_dump;


int				get_input(int argc, char **argv, t_dump *p);
int				store_args(t_dump *p);
int				gtfo(char *str);
void			print_status(char *str, t_data *ph);
long int		get_time(void);
void			usleepingood(long int time_in_ms);
int				spiderweb(t_dump *p);
void			routine(t_data *ph);
int				check_pulse(t_data *ph, int i);
int				ft_strlen(char *str);
int				ft_atoi(const char *nptr);
int				isnum(char **argv, int i, int j);
void			ft_putstr_fd(char *s, int fd);

#endif