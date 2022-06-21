# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 17:02:23 by bel-mous          #+#    #+#              #
#    Updated: 2022/06/21 20:39:47 by hakermad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	src/main.c\
		src/initializer.c\
		src/reader.c\
		src/parser.c\
		src/expander.c\
		src/execute.c\
		src/clear.c\
		src/utils.c\
		src/syntax_utils.c\
		src/debug.c\
		src/syntax_error.c\
		src/builtins/builtins_utils.c\
		src/builtins/ft_export.c\
		src/builtins/ft_unset.c\
		src/builtins/ft_env.c\
		src/builtins/ft_pwd.c\
		src/builtins/ft_cd.c\
		src/builtins/ft_echo.c\
		src/builtins/ft_shlvl.c\
		src/builtins/ft_mon_at.c\
		src/builtins/ft_signal.c\

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
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline -L./libft -lft -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

	
clean:
	make clean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	rm -f libft/libft.a
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re libft
