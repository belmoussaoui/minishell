/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/16 13:50:55 by bel-mous         ###   ########.fr       */
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

typedef struct s_data
{
	int		error_code;
	bool	s_quote;
	bool	d_quote;
	int		len_env;
	t_list	*new_env;
	char	*line;
	char	*cmd;
	char	**paths;
	char	**elements;
	t_list	*commands;
}	t_data;

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;
}	t_cmd;

void	write_error(char *message, int code);

void	initializer(t_data *data, char *envp[]);

char	*reader(t_data *data);

int		syntax_error(t_data *data);

int		parser(t_data *data, t_list **commands, char *line);

void	expander(t_list *commands);

void	execute(t_data *data, char *envp[]);
void	run_builtin(t_data *data, char *cmd_name, char *envp[]);
int		is_builtin(char *cmd_name);

void	clear(t_data *data, char *line);

void	ft_unset(t_data *data, char *envp[]);

void	ft_export(t_data *data, t_list **new_env);

// UTILS

int		is_metachar(char c);
int		check_quote(t_data *data, char c);
void	clear_quote(t_data *data);
void	ft_close(t_list *commands);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
void	debug_list(t_list *commands);
void	debug_env(t_list *env);

#endif