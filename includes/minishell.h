/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/06 17:36:13 by lrondia          ###   ########.fr       */
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
	char	*cmd;
	char	**args;
	char	**path_cmd;
	char	*paths;
}	t_data;

// EXEC

char	*path_finder(char **envp);
char	*cmd_ok(char **paths, char *cmd);
void	exec(t_data *data, char *line, char *envp[]);

// PARSING

void	parsing(char *line);
int		init_list_cmd(char *line, t_list *commands);

// UTILS

void	write_error(char *message, int code);

#endif