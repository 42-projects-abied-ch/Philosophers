# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 18:42:13 by abied-ch          #+#    #+#              #
#    Updated: 2023/10/27 16:06:14 by abied-ch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = obj

SRC_DIR = src

SRCS = 	${SRC_DIR}/utils.c \
		${SRC_DIR}/philo.c \
		${SRC_DIR}/initialize.c \
		${SRC_DIR}/get_input.c \
		${SRC_DIR}/threads.c \
		${SRC_DIR}/misc_philo.c \
		${SRC_DIR}/routine.c \
				
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

RM = rm -rf

.SILENT:

all: $(OBJ_DIR) $(NAME) 

$(NAME): $(OBJS) $(LIBFT_OBJS)
	printf "\r\rCooking.."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME)
	printf "\rFood is ready!\n"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
