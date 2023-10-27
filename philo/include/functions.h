/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:21:56 by arthur            #+#    #+#             */
/*   Updated: 2023/10/27 03:04:32 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

/*INPUT READING/PARSING*/
int				get_input(int argc, char **argv, t_dump *p);
int				store_args(t_dump *p);

/*UTILS*/
int				ft_strlen(char *str);
int				gtfo(char *str);
int				isnum(char **argv, int i, int j);
int				ft_atoi(const char *nptr);
void			print_status(char *str, t_data *ph);
void			ft_putstr_fd(char *s, int fd);
void			usleepingood(long int time_in_ms);
long int		get_time(void);

/*THREADING*/
int				spiderweb(t_dump *p);
int				check_pulse(t_data *ph, int i);
void			routine(t_data *ph);

#endif