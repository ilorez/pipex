# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/25 16:09:52 by znajdaou          #+#    #+#              #
#    Updated: 2025/01/14 17:31:41 by znajdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs

BUILD_DR = ./build/
NAME = pipex

LIBFT_DR = ./libft

FLAGS = -Wall -Wextra -Werror -ggdb # -fsanitize=address
INCLUDES_DRS = -I./includes -I./libft/includes
CC = cc
AR = ar rc
RM = rm -f

SRCS= pipex.c run_commands.c utils.c
OBJS = $(addprefix $(BUILD_DR),$(SRCS:%.c=%.o))

green = \033[32m
reset = \033[0m

all: $(NAME)
	@echo "$(green)SUCCESS!!!$(reset)"

$(BUILD_DR)%.o: %.c | $(BUILD_DR)
	$(CC) $(FLAGS) $(INCLUDES_DRS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DR)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDES_DRS) $(LIBFT_DR)/libft.a -o $(NAME)

$(BUILD_DR):
	mkdir -p $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DR) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

VALFLAGS= --leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \
					--trace-children=yes \
					--trace-children-skip='*/bin/*,*/sbin/*' 

run: 
	valgrind $(VALFLAGS) ./pipex /dev/stdin "grep salam" "grep salam1" "grep salam12" "grep salam123" /dev/stdout

run_h: 
	valgrind $(VALFLAGS) ./pipex here_doc EOF "grep salam" "grep salam1" "grep salam12" "grep salam123" /dev/stdout

run_h2: 
	valgrind $(VALFLAGS) ./pipex here_doc EOF "grep salam" "grep salam1" "grep salam12" "grep salam123" /dev/stdout



.PHONY: all clean fclean re bonus
