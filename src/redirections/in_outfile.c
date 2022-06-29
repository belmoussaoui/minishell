/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:35:10 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/29 16:16:18 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_cmd *cmd, char *infile)
{
	cmd->is_redirection = 0;
	cmd->fd_redirection = open(infile, O_RDONLY);
	if (cmd->fd_redirection == -1)
		werror("No such file or directory", 1);
}

void	handle_outfile(t_cmd *cmd, char *outfile)
{
	cmd->is_redirection = 1;
	cmd->fd_redirection = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_redirection == -1)
		werror("No such file or directory", 1);
}

void	handle_outfile_append(t_cmd *cmd, char *outfile)
{
	cmd->is_redirection = 1;
	cmd->fd_redirection = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_redirection == -1)
		werror("No such file or directory", 1);
}
