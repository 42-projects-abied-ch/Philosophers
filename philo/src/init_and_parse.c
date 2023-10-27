#include "../include/philosophers.h"

void	mutex(t_dump *dump)
{
	pthread_mutex_init(&dump->args.write_mutex, NULL);
	pthread_mutex_init(&dump->args.dead, NULL);
	pthread_mutex_init(&dump->args.time_eat, NULL);
	pthread_mutex_init(&dump->args.finish, NULL);
}

int	store_args(t_dump *dump)
{
	int	i;

	i = 0;
	dump->args.start_t = get_time();
	dump->args.stop = 0;
	dump->args.nb_p_finish = 0;
	mutex(dump);
	while (i < dump->args.philo_count)
	{
		dump->data[i].id = i + 1;
		dump->data[i].ms_eat = dump->args.start_t;
		dump->data[i].nb_eat = 0;
		dump->data[i].finish = 0;
		dump->data[i].r_f = NULL;
		pthread_mutex_init(&dump->data[i].l_f, NULL);
		if (dump->args.philo_count == 1)
			return (1);
		if (i == dump->args.philo_count - 1)
			dump->data[i].r_f = &dump->data[0].l_f;
		else
			dump->data[i].r_f = &dump->data[i + 1].l_f;
		i++;
	}
	return (1);
}
