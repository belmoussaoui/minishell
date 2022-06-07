/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:34:39 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/07 20:17:18 by lrondia          ###   ########.fr       */
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
	while (line && line[len] && !is_charset(line[len]))
		len++;
	if (is_charset(line[len]) && len == 0)
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

int	init_list_cmd(char *line, t_list *commands)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[i] && !is_charset(line[i]))
		create_new_list(&commands, line);
	while (line[i])
	{
		if (is_charset(line[i]))
			create_new_list(&commands, line + i);
		if (line[i - 1] && is_charset(line[i - 1]) && !is_charset(line[i]))
		{
			create_new_list(&commands, line + i);
			i++;
		}
		i++;
	}
	return (1);
}
