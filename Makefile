# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/25 14:30:53 by joaqumar          #+#    #+#              #
#    Updated: 2026/05/06 19:55:49 by joaqumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs

HEADER		= ft_printf.h

SRC			= ft_printf.c \
			  ft_parser.c \
			  ft_dispatch.c \
			  ft_utils.c \
			  ft_print_nums.c \
			  ft_print_hex.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)

bonus : all

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@echo 
	@echo "✅ Librería $(NAME) creada con éxito."
	@echo

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@
test: all
	$(CC) $(CFLAGS) main.c libftprintf.a -o test
	./test
clean:
	$(RM) $(OBJ)
	@echo
	@echo "🧹 Archivos objeto eliminados."
	@echo

fclean: clean
	$(RM) $(NAME)
	@echo
	@echo "🗑️ Librería $(NAME) eliminada."
	@echo

re: fclean all

.PHONY: all bonus clean fclean re
