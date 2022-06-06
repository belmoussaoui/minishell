/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:04:28 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/06 17:11:40 by hakermad         ###   ########.fr       */
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

char	*path_finder(char **envp);
void	write_error(char *message, int code);
char	*cmd_ok(char **paths, char *cmd);
void	exec(t_data *data, char *line, char *envp[]);
int		init_list_cmd(char *line, t_list *commands);

#endif