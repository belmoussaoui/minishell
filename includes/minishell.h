/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/07 19:54:46 by lrondia          ###   ########.fr       */
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

	int		error_code;
}	t_data;

// EXEC

char	*cmd_ok(char **paths, char *cmd);
void	exec(t_data *data, char *line, char *envp[]);

// PARSING

int		parsing(t_data *data, char *line);
int		init_list_cmd(char *line, t_list *commands);

// UTILS

int		is_charset(char c);
void	werror(t_data *data, char *message, int code);
void	werror_exit(t_data *data, char *message, int code);

#endif