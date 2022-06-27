/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:08:51 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/27 20:52:51 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_the_split(char **split)
{
	int		i;
	char	*copy;
	char	*str;

	i = 0;
	str = malloc(1);
	if (!str)
		exit (EXIT_FAILURE);
	str[0] = '\0';
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
	while (line[i] == ' ')
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
		copy = copy->next;
	}
}
