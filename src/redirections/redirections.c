/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:42:11 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/20 19:55:00 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_infile(t_data *data, t_cmd *cmd, char *line)
{
	int		len;
	char	*infile;

	len = 0;
	infile = get_file(line);
	cmd->infile = open(infile, O_RDONLY);
	if (cmd->infile == -1)
		werror_exit(data, "can't open, error occured", 1);
}

void	handle_outfile(t_data *data, t_cmd *cmd, char *line)
{
	int		len;
	char	*outfile;

	len = 0;
	outfile = get_file(line);
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		werror_exit(data, "can't open, error occured", 1);
}

void	handle_outfile_append(t_data *data, t_cmd *cmd, char *line)
{
	int		len;
	char	*outfile;

	len = 0;
	outfile = get_file(line);
	cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile == -1)
		werror_exit(data, "can't open, error occured", 1);
}

void	handle_fd(t_data *data, t_cmd *cmd, char **elements, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			if (line[i + 2] != '\0')
				handle_heredoc(data, cmd, elements[0] + 2);
			else
				handle_heredoc(data, cmd, elements[1]);
			i++;
		}
		else if (line[i] == '<' && line[i] != '<')
			handle_infile(data, cmd, line + 1);
		else if (line[i] == '>' && line[i] != '<')
			handle_outfile(data, cmd, line + 2);
		else if (line[i] == '>' && line[i] == '>')
		{
			handle_outfile_append(data, cmd, line);
			i++;
		}
		i++;
	}
}

void	redirections(t_data *data, t_list *commands)
{
	int		i;
	t_cmd	*content;

	while (commands)
	{
		i = 0;
		content = (t_cmd *)(commands->content);
		while (content->elements[i])
		{
			handle_fd(data, content, content->elements + i,
				content->elements[i]);
			i++;
		}
		commands = commands->next;
	}
}
