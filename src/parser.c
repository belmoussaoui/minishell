/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:34:39 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/15 19:52:07 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(t_data *data, char *line)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	if (!line)
		return (line);
	while (line[len] && ((check_quote(data, line[len])
				&& is_metachar(line[len])) || !is_metachar(line[len])))
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
	clear_quote(data);
	return (tmp);
}

void	in_out_file(t_data *data, t_cmd *cmd)
{
	int		tab[2];

	if (pipe(tab) == -1)
		werror_exit(data, "can't pipe, error occured\n", 127);
	cmd->infile = tab[0];
	cmd->outfile = tab[1];
}

void	lexer(t_data *data, t_list **commands, char *line)
{
	t_list	*new;
	t_cmd	*cmd;
	char	*tmp;

	cmd = malloc(sizeof(t_cmd *));
	if (!cmd)
		exit(EXIT_FAILURE);
	tmp = get_command(data, line);
	cmd->elements = ft_split(tmp, ' ');
	if (!cmd->elements)
		exit(EXIT_FAILURE);
	in_out_file(data, cmd);
	new = ft_lstnew(cmd);
	if (!new)
		exit(EXIT_FAILURE);
	ft_lstadd_back(commands, new);
	free(tmp);
}

// Transforms a command line into a list of tokens
int	parser(t_data *data, t_list **commands, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	lexer(data, commands, line);
	while (line[i])
	{
		if (!check_quote(data, line[i]) && is_metachar(line[i]))
			lexer(data, commands, line + i + 1);
		i++;
	}
	clear_quote(data);
	return (1);
}
