/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:34:39 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/02 19:36:40 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset(char	c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char *get_command(char *line)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	if (is_charset(line[len]))
		len++;
	while (line && line[len] && !is_charset(line[len]))
		len++;
	tmp = malloc(sizeof(char) * len + 1);
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
	char *tmp;

	tmp = get_command(line);
	new = ft_lstnew(tmp);
	if (!new)
		exit(0);
	ft_lstadd_back(commands, new);
}

int	init_list_cmd(char *line, t_list *commands)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	create_new_list(&commands, line);
	while (line && line[i])
	{
		if (is_charset(line[i]))
			create_new_list(&commands, line + i);
		i++;
	}
	return (1);
}
