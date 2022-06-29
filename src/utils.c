/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:08:51 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/29 17:44:35 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_the_split(char **split)
{
	int		i;
	char	*copy;
	char	*str;

	i = 0;
	str = "";
	while (split[i])
	{
		copy = ft_strjoin(str, split[i]);
		if (!copy)
			exit(EXIT_FAILURE);
		str = copy;
		free(copy);
		i++;
	}
	return (str);
}

int	is_only_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

void	werror(char *message, int code)
{
	int	len;

	len = ft_strlen(message);
	g_error_code = code;
	write(2, message, len);
	write(2, "\n", 1);
}

void	werror_exit(char *message, int code)
{
	int	len;

	len = ft_strlen(message);
	g_error_code = code;
	write(2, message, len);
	write(2, "\n", 1);
	exit(code);
}

void	ft_close(t_list *commands)
{
	int		i;
	t_list	*copy;

	i = 0;
	copy = commands;
	while (copy)
	{
		close(((t_cmd *)(copy->content))->infile);
		close(((t_cmd *)(copy->content))->outfile);
		if (((t_cmd *)(copy->content))->is_redirection != -1)
			close(((t_cmd *)(copy->content))->fd_redirection);
		copy = copy->next;
	}
}
