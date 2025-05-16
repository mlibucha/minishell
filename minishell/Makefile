# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: e <e@student.42.fr>                        +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/04/24 14:08:20 by e                 #+#    #+#             #
#   Updated: 2025/04/28 10:48:23 by e                ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = mini

# Sources
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Readline library flags (adjust paths if needed)
RL_FLAGS = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

# Libft paths (adjust if needed)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
LIBFT_LINK = -L$(LIBFT_DIR) -lft

all: $(NAME)

# Rule to build libft first
$(LIBFT):
	make -C $(LIBFT_DIR)

# Link with libft and readline
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LINK) $(RL_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re