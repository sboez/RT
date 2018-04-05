# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shiro <shiro@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 15:55:46 by fcecilie          #+#    #+#              #
#    Updated: 2018/02/19 13:52:11 by shiro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================ #

NAME = libft.a

SRC_LIBFT = ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_intlen.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_cnt_fgr.c \
			ft_div_nbr.c \
			ft_putnstr.c \
			ft_puttab.c \
			ft_abs.c \
			ft_strnlen.c \
			ft_realloc.c \
			ft_cnt_word.c \
			get_next_line.c \
			get_file_to_string.c \
			ft_itoa_base.c \
			ft_utoa_base.c \
			errors.c \
			ft_angles.c \
			ft_minmax.c \
			garbage_collector.c\
			ft_mod.c

INCLUDE = libft.h \

INCLUDE := $(addprefix includes/, $(INCLUDE))
SRC_LIBFT := $(addprefix sources/, $(SRC_LIBFT))

OBJ = $(SRC_LIBFT:.c=.o)

# ============================================ #

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c $(INCLUDE)
	@$(CC) -Wall -Wextra -Werror -o $@ -c $< -I includes/

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
