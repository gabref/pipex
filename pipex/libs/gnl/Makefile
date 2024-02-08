# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 20:31:25 by galves-f          #+#    #+#              #
#    Updated: 2024/02/07 17:46:15 by galves-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libgnl.a
SRC 	= get_next_line_bonus.c get_next_line_utils_bonus.c
OBJ 	= $(SRC:.c=.o)
INC 	= . 
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re .c.o
