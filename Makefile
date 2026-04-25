# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/25 14:30:53 by joaqumar          #+#    #+#              #
#    Updated: 2026/04/25 14:43:46 by joaqumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

# Compilador y Flags
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
AR			= ar rcs

# Archivos de cabecera
HEADER		= ft_printf.h

# Listado de archivos fuente
SRC			= ft_printf.c \
			  ft_parser.c \
			  ft_dispatch.c \
			  ft_utils.c \
			  ft_print_nums.c \
			  ft_print_hex.c

# Transformación de .c a .o
OBJ			= $(SRC:.c=.o)

# Regla principal
all: $(NAME)

# Creación de la librería
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@echo 
	@echo "✅ Librería $(NAME) creada con éxito."
	@echo

# Compilación de objetos individuales
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	$(RM) $(OBJ)
	@echo
	@echo "🧹 Archivos objeto eliminados."
	@echo

# Limpiar objetos y la librería
fclean: clean
	$(RM) $(NAME)
	@echo
	@echo "🗑️ Librería $(NAME) eliminada."
	@echo

# Re-compilar todo
re: fclean all

# Indicar que estas reglas no son archivos
.PHONY: all clean fclean re
