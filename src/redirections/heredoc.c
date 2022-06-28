/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:47:26 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/28 13:35:26 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_stdin(char *stop, int file_id)
{
	char	*gnl;

	write(1, "> ", 2);
	gnl = get_next_line(0);
	while (gnl && !(!ft_strncmp(gnl, stop, ft_strlen(stop))
			&& ft_strlen(gnl) - 1 == ft_strlen(stop)))
	{
		write (file_id, gnl, ft_strlen(gnl));
		free (gnl);
		write(1, "> ", 2);
		gnl = get_next_line(0);
	}
	if (gnl)
		free (gnl);
}

void	handle_heredoc(t_cmd *cmd, char *stop)
{
	cmd->is_redirection = 0;
	close (cmd->infile);
	cmd->infile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->infile == -1)
		werror_exit("can't open, error occured", 1);
	write_stdin(stop, cmd->infile);
	close (cmd->infile);
	cmd->infile = open(".heredoc", O_RDONLY, 0644);
	if (cmd->infile == -1)
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
		j = 0;
		while (line[j])
		{
			if (is_metachar(line[j]))
			{
				if (j == 0)
					elements[i] = NULL;
				else
					line[j] = '\0';
				elements[i + 1] = NULL;
				return ;
			}
			j++;
		}
		i++;
	}
}
