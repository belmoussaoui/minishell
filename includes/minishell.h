/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/13 04:06:21 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	*line;
	t_list	*commands;
	char	*cmd;
	char	**args;
	char	**path_cmd;
	char	*paths;
}	t_data;

void	write_error(char *message, int code);

void	initializer(t_data *data, int argc, char *argv[], char *envp[]);

char	*reader(void);

void	initializer(t_data *data, int argc, char *argv[], char *envp[]);

int		lexer(char *line, t_list *commands);

void	parser(t_list *commands);

void	expander(t_list *commands);

void	execute(t_data *data, char *line, char *envp[]);

void	clear(t_data *data, char *line);

#endif