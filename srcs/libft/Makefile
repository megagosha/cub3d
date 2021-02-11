# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 21:47:39 by edebi             #+#    #+#              #
#    Updated: 2020/12/30 18:35:28 by edebi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc -O3

CFLAGS = -Wall -Wextra -Werror

# LDFLAGS=-L.

# LDLIBS=-lft

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
       ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	   ft_issprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	   ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	   ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	   ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			 ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			 ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

$(NAME): ${OBJS} libft.h
		 ar -crs ${NAME} ${OBJS}

.c.o:
	${CC} ${CFLAGS} ${OPTIONS} $< -o $@ -c

all: ${NAME}

bonus: ${OBJS} ${OBJS_BONUS}
	  ar -crs ${NAME} ${OBJS} ${OBJS_BONUS}

clean:
	rm -rf ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean fclean all re bonus

# ifdef BONUS
# OBJ_FILES = $(OBJS) $(OBJS_BONUS)
# else
# OBJ_FILES = $(OBJS)
# endif

# bonus:
# 	$(MAKE) BONUS=1 all
