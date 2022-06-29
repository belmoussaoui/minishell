/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:47:26 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/30 01:14:22 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_stdin(char *stop, int file_id)
{
	char	*gnl;

	gnl = readline("> ");
	while (gnl && !(!ft_strncmp(gnl, stop, ft_strlen(stop))
			&& ft_strlen(gnl) == ft_strlen(stop)))
	{
		write (file_id, gnl, ft_strlen(gnl));
		write (file_id, "\n", ft_strlen("\n"));
		free (gnl);
		gnl = readline("> ");
	}
	if (gnl)
		free (gnl);
}

void	handle_heredoc(t_cmd *cmd, char *stop)
{
	cmd->is_redirection = 0;
	cmd->fd_redirection = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_redirection == -1)
		werror_exit("can't open, error occured", 1);
	write_stdin(stop, cmd->fd_redirection);
	close (cmd->fd_redirection);
	cmd->fd_redirection = open(".heredoc", O_RDONLY, 0644);
	if (cmd->fd_redirection == -1)
		werror_exit("can't open, error occured", 1);
}

void	clear_redirection(char **elements)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (elements[i])
	{
		line = elements[i];
		if (is_metachar(line[0]))
		{
			j = i;
			while (elements[i + 2])
			{
				elements[i] = elements[i + 2];
				i++;
			}
			elements[i] = NULL;
			break ;
		}
		i++;
	}
}
