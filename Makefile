# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/19 11:40:47 by znajdaou          #+#    #+#              #
#    Updated: 2025/01/21 18:58:38 by znajdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c bonus
vpath %.c srcs
vpath %.c utils

BUILD_DR = ./build/
NAME = pipex
BONUS_NAME = pipex_bonus

LIBFT_DR = ./libft

FLAGS = -Wall -Wextra -Werror #-g3 #-fsanitize=address
INCLUDES_DRS = -I./includes -I./libft/includes
CC = cc
AR = ar rc
RM = rm -f

SRCS= 

UTILS_SRCS =  

BONUS_SRCS=  pipex_bonus.c run_commands.c utils.c \
						 on_errors.c init_data.c here_doc.c \
						 handle_exit.c child.c wait_macros.c

OBJS = $(addprefix $(BUILD_DR),$(SRCS:%.c=%.o))
UTILS_OBJS = $(addprefix $(BUILD_DR),$(UTILS_SRCS:%.c=%.o))
BONUS_OBJS = $(addprefix $(BUILD_DR),$(BONUS_SRCS:%.c=%.o))
green = \033[32m
reset = \033[0m

all: $(NAME)
	@echo "$(green)MANDATORY SUCCESS!!!$(reset)"

$(BUILD_DR)%.o: %.c | $(BUILD_DR)
	$(CC) $(FLAGS) $(INCLUDES_DRS) -c $< -o $@

$(NAME): $(OBJS) $(UTILS_OBJS)
	make -C $(LIBFT_DR)
	$(CC) $(FLAGS) $(OBJS) $(UTILS_OBJS) $(INCLUDES_DRS) $(LIBFT_DR)/libft.a -o $(NAME)

bonus: $(BONUS_NAME)
	@echo "$(green)BONUS SUCCESS!!!$(reset)"

$(BONUS_NAME): $(BONUS_OBJS) $(UTILS_OBJS)
	make -C $(LIBFT_DR)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(UTILS_OBJS) $(INCLUDES_DRS) $(LIBFT_DR)/libft.a -o $(BONUS_NAME)

$(BUILD_DR):
	mkdir -p $@

clean:
	$(RM) $(OBJS) $(UTILS_OBJS) $(BONUS_OBJS)
	make -C $(LIBFT_DR) fclean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
