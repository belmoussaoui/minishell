/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:35:10 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/28 13:33:04 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_cmd *cmd, char *infile)
{
	cmd->is_redirection = 0;
	close (cmd->infile);
	cmd->infile = open(infile, O_RDONLY);
	if (cmd->infile == -1)
		werror("No such file or directory", 1);
}

void	handle_outfile(t_cmd *cmd, char *outfile)
{
	cmd->is_redirection = 1;
	close (cmd->outfile);
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		werror("No such file or directory", 1);
}

void	handle_outfile_append(t_cmd *cmd, char *outfile)
{
	cmd->is_redirection = 1;
	close (cmd->outfile);
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile == -1)
		werror("No such file or directory", 1);
}
