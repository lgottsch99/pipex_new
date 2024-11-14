# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Watanudon <Watanudon@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 13:54:41 by lgottsch          #+#    #+#              #
#    Updated: 2024/11/14 17:38:11 by Watanudon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#call makefile from libft first
#somehow make it all one program here

NAME = pipex

CC= cc
CFLAGS= -Werror -Wall -Wextra


SRC =  pipex.c children.c execute.c\
		full_libft/full_libft.a

OBJ = $(SRC:.c=.o)
LIBFTDIR= ./full_libft


$(NAME): 
	@make -C full_libft
	$(CC) $(CFLAGS) $(SRC) -o pipex

all: $(NAME)


clean:
	rm -f $(OBJ)
	@cd $(LIBFTDIR) && make clean

fclean: clean
	rm -f $(NAME)
	@cd $(LIBFTDIR) && make clean

re: fclean all 


.PHONY: all clean fclean re