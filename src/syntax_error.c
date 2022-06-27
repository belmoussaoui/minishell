/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:54 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/27 19:56:48 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_wrong_seperators(t_data *data, char *line)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (line[i])
	{
		if (!check_quote(data, line[i]) && line[i] == '|')
		{
			nb_pipe++;
			if (nb_pipe == 3 || (nb_pipe == 2 && line[i - 1] != '|'))
			{
				werror("syntax error near unexpected token `|'", 285);
				break ;
			}
			else if (line[i] == '|' && i != 0 && line[i - 1] == '<')
			{
				werror("syntax error near unexpected token `|'", 285);
				break ;
			}
		}
		if (ft_isalnum(line[i]))
			nb_pipe = 0;
		i++;
	}
}

void	begin_end_with_separator(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		werror("syntax error near unexpected token `|'", 285);
	i = ft_strlen(line) - 1;
	if (line[i] == '<' || line[i] == '>')
		werror("syntax error near unexpected token `newline'", 285);
}

int	syntax_error(t_data *data)
{
	check_wrong_seperators(data, data->line);
	if (check_quote(data, 'c'))
		werror("syntax error near unexpected token `quote'", 285);
	clear_quote(data);
	begin_end_with_separator(data->line);
	if (g_error_code == 285)
		return (0);
	return (1);
}
