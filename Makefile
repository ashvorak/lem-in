# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 15:12:57 by oshvorak          #+#    #+#              #
#    Updated: 2018/04/12 12:08:39 by oshvorak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIB = lib.a

CFLAGS = -Wall -Wextra -Werror -I$(INC)

SRC = ./src/main.c \
	  ./src/valid.c	 \
	  ./src/read_rooms.c \
	  ./src/read_connections.c \
	  ./src/map_join.c \
	  ./src/handle_paths.c \
	  ./src/wave_tracing.c \
	  ./src/print_paths.c \
	  ./src/free_farm.c \
	  ./src/process_path.c \
	  ./src/handle_flags.c

GNL = ./lib/get_next_line/get_next_line.c

FT_PRINTF = ./lib/ft_printf/src/active_bits.c \
			./lib/ft_printf/src/convert_base.c \
			./lib/ft_printf/src/convert_int.c \
			./lib/ft_printf/src/convert_float.c \
			./lib/ft_printf/src/ft_printf.c \
			./lib/ft_printf/src/ft_putwchar.c \
			./lib/ft_printf/src/handle_char.c \
			./lib/ft_printf/src/handle_n.c \
			./lib/ft_printf/src/handle_num.c \
			./lib/ft_printf/src/handle_float.c \
			./lib/ft_printf/src/handle_str.c \
			./lib/ft_printf/src/handle_qualifier.c \
			./lib/ft_printf/src/handle_value.c \
			./lib/ft_printf/src/handle_wchar.c \
			./lib/ft_printf/src/handle_wstr.c \
			./lib/ft_printf/src/is_type.c \
			./lib/ft_printf/src/ft_realloc.c \
			./lib/ft_printf/src/make_colors.c \
			./lib/ft_printf/src/size_char.c

LIBFT = ./lib/ft_atoi.c \
		./lib/ft_bzero.c \
		./lib/ft_isalnum.c \
		./lib/ft_isalpha.c \
		./lib/ft_isascii.c \
		./lib/ft_isdigit.c \
		./lib/ft_isprint.c \
		./lib/ft_itoa.c \
		./lib/ft_lstadd.c \
		./lib/ft_lstdel.c \
		./lib/ft_lstdelone.c \
		./lib/ft_lstiter.c \
		./lib/ft_lstmap.c \
		./lib/ft_lstnew.c \
		./lib/ft_memalloc.c \
		./lib/ft_memccpy.c \
		./lib/ft_memchr.c \
		./lib/ft_memcmp.c \
		./lib/ft_memcpy.c \
		./lib/ft_memdel.c \
		./lib/ft_memmove.c \
		./lib/ft_memset.c \
		./lib/ft_putchar.c \
		./lib/ft_putchar_fd.c \
		./lib/ft_putendl.c \
		./lib/ft_putendl_fd.c \
		./lib/ft_putnbr.c \
		./lib/ft_putnbr_fd.c \
		./lib/ft_putstr.c \
		./lib/ft_putstr_fd.c \
		./lib/ft_strcat.c \
		./lib/ft_strchr.c \
		./lib/ft_strclr.c \
		./lib/ft_strcmp.c \
		./lib/ft_strcpy.c \
		./lib/ft_strdel.c \
		./lib/ft_strdup.c \
		./lib/ft_strequ.c \
		./lib/ft_striter.c \
		./lib/ft_striteri.c \
		./lib/ft_strjoin.c \
		./lib/ft_strlcat.c \
		./lib/ft_strlen.c \
		./lib/ft_strmap.c \
		./lib/ft_strmapi.c \
		./lib/ft_strncat.c \
		./lib/ft_strncmp.c \
		./lib/ft_strncpy.c \
		./lib/ft_strnequ.c \
		./lib/ft_strnew.c \
		./lib/ft_strnstr.c \
		./lib/ft_strrchr.c \
		./lib/ft_strsplit.c \
		./lib/ft_strstr.c \
		./lib/ft_strsub.c \
		./lib/ft_strtrim.c \
		./lib/ft_tolower.c \
		./lib/ft_toupper.c \
		./lib/ft_swap.c \
		./lib/ft_sqrt.c \
		./lib/ft_strcapitalize.c \
		./lib/ft_factorial.c \
		./lib/ft_listsize.c \
		./lib/ft_charreplace.c \
		./lib/ft_atoi_base.c \
		./lib/ft_array_size.c \
		./lib/ft_free_arr.c \
		./lib/ft_free_arr_int.c

INC = ./inc

LIBFT_OBJ = $(LIBFT:.c=.o)

FT_PRINTF_OBJ = $(FT_PRINTF:.c=.o)

GNL_OBJ = $(GNL:.c=.o)

all: $(NAME)

$(NAME): $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)
	ar rc $(LIB) $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)
	ranlib $(LIB)
	gcc $(CFLAGS) $(SRC) $(LIB) -o $(NAME)

clean:
	/bin/rm -f $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)
fclean:	clean
	/bin/rm -f $(NAME) $(LIB)

re: fclean all
