/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:42:11 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/23 19:35:09 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fd(t_data *data, t_cmd *cmd, char **elements, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '<' && line[i] != '>')
		i++;
	if (line[i] == '<' && line[i + 1] == '<')
		handle_heredoc(data, cmd, elements[1]);
	else if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] == '\0')
		handle_infile(data, cmd, elements[1]);
	else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] == '\0')
		handle_outfile(data, cmd, elements[1]);
	else if (line[i] == '>' && line[i + 1] == '>')
		handle_outfile_append(data, cmd, elements[1]);
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
