/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/15 13:35:08 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;
}	t_cmd;

typedef struct s_environment
{
	char	**environment;
	char	*before;
	char	*after;
}	t_environment;

typedef struct s_data
{
	char					*line;
	t_list					*commands;
	char					*cmd;
	char					**args;
	char					**path_cmd;
	char					*paths;
	struct s_environment	*environment;
	int		error_code;

}	t_data;

void	initializer(t_data *data, int argc, char *argv[], char *envp[]);

char	*reader(void);

int		syntax_error(t_data *data);

int		parser(t_list **commands, char *line);

void	expander(t_list *commands);

void	execute(t_data *data, char *envp[]);

void	clear(t_data *data, char *line);

// UTILS

int		is_metachar(char c);
void	ft_close(t_list *commands);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
void	debug_list(t_list *commands);

#endif