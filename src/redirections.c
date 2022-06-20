/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:42:11 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/20 15:45:24 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_data *data, t_cmd *cmd)
{
	(void) data;
	(void) cmd;
}

void	handle_infile(t_data *data, t_cmd *cmd)
{
	(void) data;
	(void) cmd;
}

void	handle_outfile(t_data *data, t_cmd *cmd)
{
	(void) data;
	(void) cmd;
}

void	handle_outfile_append(t_data *data, t_cmd *cmd)
{
	(void) data;
	(void) cmd;
}

void	redirections(t_data *data, t_cmd *cmd, char *line)
{
	if (line[0] == '<' && line[1] == '<')
		handle_heredoc(data, cmd);
	else if (line[0] == '<' && line[1] != '<')
		handle_infile(data, cmd);
	else if (line[0] == '>' && line[1] != '<')
		handle_outfile(data, cmd);
	else if (line[0] == '>' && line[1] == '>')
		handle_outfile_append(data, cmd);
}