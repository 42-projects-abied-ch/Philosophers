#include "../include/philosophers.h"

int	isnum(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long	sign;
	long	base;
	long	i;

	sign = 1;
	base = 0;
	i = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = 1 - 2 * (nptr[i++] == '-');
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (base > 2147483647 / 10
			|| (base == 2147483647 / 10 && nptr[i] - '0' > 7))
		{
			if (sign == 1)
				return (2147483647);
		}
		base = 10 * base + (nptr[i++] - '0');
		if (base < -2147483648)
			return (-2147483648);
	}
	return (base * sign);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
