/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 13:55:06 by lrondia          ###   ########.fr       */
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

typedef struct s_data
{
	char	*line;
	t_list	*commands;
	char	*cmd;
	char	**args;
	char	**path_cmd;
	char	*paths;

	int		error_code;
}	t_data;

void	initializer(t_data *data, int argc, char *argv[], char *envp[]);

char	*reader(void);

int		syntax_error(t_data *data);

int		parser(t_list *commands, char *line);

void	expander(t_list *commands);

void	execute(t_data *data, char *envp[]);

void	clear(t_data *data, char *line);

// UTILS

int		is_metachar(char c);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
void	debug_list(t_list *commands);

#endif