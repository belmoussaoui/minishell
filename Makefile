# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 17:02:23 by bel-mous          #+#    #+#              #
#    Updated: 2022/06/13 12:29:18 by lrondia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	src/main.c\
		src/initializer.c\
		src/reader.c\
		src/lexer.c\
		src/parser.c\
		src/expander.c\
		src/execute.c\
		src/clear.c\
		src/utils.c\

INCLUDES = includes
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc
$(RM) = rm -rf

all: libft $(NAME)

libft:
	@make -C ./libft
	
.c.o: $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline -L./libft -lft

clean:
	make clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	rm -f libft/libft.a
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re libft
