/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/15 19:42:37 by hakermad         ###   ########.fr       */
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
	char	*line;
	t_list	*commands;
	char	*cmd;
	char	**elements;
	char	**paths;
	int		error_code;
	int		len_env;
	t_list	*new_env;
}	t_data;

typedef struct s_cmd
{
	char	**elements;
	int		infile;	
	int		outfile;
}	t_cmd;

void	write_error(char *message, int code);

void	initializer(t_data *data, char *envp[]);

char	*reader(void);

void	lexer(t_list **commands, char *line);

int		syntax_error(t_data *data);

int		parser(t_list **commands, char *line);

void	expander(t_list *commands);

void	execute(t_data *data, char *envp[]);

void	clear(t_data *data, char *line);

void	ft_unset(t_data *data, char *envp[]);

void	ft_export(t_data *data, t_list **new_env);


// UTILS

int		is_metachar(char c);
void	ft_close(t_list *commands);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);
void	debug_list(t_list *commands);
void	debug_env(t_list *env);

#endif