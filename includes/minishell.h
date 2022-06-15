/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 17:58:36 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_environment
{
	char	**environment;
	char	*name;
	char	*value;
	char	*before;
	char	*after;
	char	*new;

	void			*content;
	struct s_list	*next;
}	t_environment;

typedef struct s_data
{
	char					*line;
	t_list					*commands;
	char					*cmd;
	char					**args;
	char					**path_cmd;
	char					*paths;
	int		error_code;
	struct s_environment	*environment;
}	t_data;

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;	
}	t_cmd;

void	write_error(char *message, int code);

void	initializer(t_data *data, int argc, char *argv[], char *envp[]);

char	*reader(void);

void	lexer(t_list **commands, char *line);

int		syntax_error(t_data *data);

int		parser(t_list **commands, char *line);

void	expander(t_list *commands);

void	execute(t_data *data, char *envp[]);

void	clear(t_data *data, char *line);


// UTILS

int		is_metachar(char c);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
void	debug_list(t_list *commands);

#endif