/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:42:11 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/22 17:50:07 by lrondia          ###   ########.fr       */
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

void	handle_fd(t_data *data, t_cmd *cmd, char **elements, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			if (line[i + 2] && line[i + 2] != '\0')
				handle_heredoc(data, cmd, elements[0] + 2);
			else
				handle_heredoc(data, cmd, elements[1]);
			i++;
		}
		else if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != '\0')
			handle_infile(data, cmd, elements[0] + 1);
		else if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] == '\0')
			handle_infile(data, cmd, elements[1]);
		else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != '\0')
			handle_outfile(data, cmd, elements[0] + 1);
		else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] == '\0')
			handle_outfile(data, cmd, elements[1]);
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			if (line[i + 2] && line[i + 2] != '\0')
				handle_heredoc(data, cmd, elements[0] + 2);
			else
				handle_heredoc(data, cmd, elements[1]);
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
		clear_redirection(content->elements);
		commands = commands->next;
	}
}
