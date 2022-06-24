/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:35:10 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/23 19:36:55 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_data *data, t_cmd *cmd, char *infile)
{
	int		len;

	len = 0;
	cmd->infile = open(infile, O_RDONLY);
	printf("%d\n", cmd->infile);
	if (cmd->infile == -1)
		werror_exit(data, "can't open, error occured", 1);
}

void	handle_outfile(t_data *data, t_cmd *cmd, char *outfile)
{
	int		len;

	len = 0;
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		werror_exit(data, "can't open, error occured", 1);
}

void	handle_outfile_append(t_data *data, t_cmd *cmd, char *outfile)
{
	int		len;

	len = 0;
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile == -1)
		werror_exit(data, "can't open, error occured", 1);
}
