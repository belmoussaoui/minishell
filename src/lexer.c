/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:34:39 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/13 12:27:23 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*get_command(char *line)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	while (line && line[len] && !is_metachar(line[len]))
		len++;
	if (is_metachar(line[len]) && len == 0)
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

void	create_new_list(t_list **commands, char *line)
{
	t_list	*new;
	char	*tmp;
	char	**tab;

	tmp = get_command(line);
	tab = ft_split(tmp, ' ');
	free(tmp);
	new = ft_lstnew(tab);
	if (!new)
		exit(EXIT_FAILURE);
	ft_lstadd_back(commands, new);
}

// Transforms a command line into a list of tokens
int	lexer(char *line, t_list *commands)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[i] && !is_metachar(line[i]))
		create_new_list(&commands, line);
	while (line[i])
	{
		if (is_metachar(line[i]))
			create_new_list(&commands, line + i);
		if (line[i - 1] && is_metachar(line[i - 1]) && !is_metachar(line[i]))
		{
			create_new_list(&commands, line + i);
			i++;
		}
		i++;
	}
	return (1);
}
