# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 20:31:25 by galves-f          #+#    #+#              #
#    Updated: 2024/02/07 18:45:59 by galves-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
SRC 	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		  ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c ft_strchr.c \
		  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		  ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
		  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ 	= $(SRC:.c=.o)
OBJB	= $(BONUS:%.c=%.o)
INC 	= . 
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf

# SRC 	= $(wildcard *.c)
# OBJF 	= obj
# OBJB 	= $($(BONUS):%.c=$(OBJF)/%.o)
# OBJ 	= $(patsubst %.c, $(OBJF)/%.o, $(SRC))
# OBJB 	= $(patsubst %.c, $(OBJF)/%.o, $(BONUS))

# $(OBJF)/%.o: %.c
# 	mkdir -p $(OBJF)
# 	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

bonus: $(NAME) $(OBJB)
	ar rc $(NAME) $(OBJB)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re .c.o
