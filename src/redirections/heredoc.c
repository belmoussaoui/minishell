/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:47:26 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/20 19:53:57 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file(char *line)
{
	int		i;
	char	*file;

	i = 0;
	file = ft_strdup(line);
	if (!file)
		exit(EXIT_FAILURE);
	while (file[i] && file[i] != '|')
		i++;
	if (file[i] == '|')
		file[i] = '\0';
	return (file);
}

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

void	handle_heredoc(t_data *data, t_cmd *cmd, char *stop)
{
	cmd->infile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->infile == -1)
		werror_exit(data, "can't open, error occured", 1);
	write_stdin(stop, cmd->infile);
	cmd->infile = open(".heredoc", O_RDONLY, 0644);
	if (cmd->infile == -1)
		werror_exit(data, "can't open, error occured", 1);
}
