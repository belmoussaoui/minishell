/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:34:39 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/14 14:03:27 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *line)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	while (line && line[len] && !is_metachar(line[len]))
		len++;
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	lexer(t_list **commands, char *line)
{
	t_list	*new;
	t_cmd	*cmd;
	char	*tmp;

	cmd = malloc(sizeof(t_cmd *));
	if (!cmd)
		exit(EXIT_FAILURE);
	tmp = get_command(line);
	cmd->elements = ft_split(tmp, ' ');
	cmd->infile = 0;
	cmd->outfile = 1;
	new = ft_lstnew(cmd);
	if (!new)
		exit(EXIT_FAILURE);
	ft_lstadd_back(commands, new);
	free(tmp);
}

// Transforms a command line into a list of tokens
int	parser(t_list **commands, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	lexer(commands, line);
	while (line[i])
	{
		if (is_metachar(line[i]))
			lexer(commands, line + i + 1);
		i++;
	}
	return (1);
}
