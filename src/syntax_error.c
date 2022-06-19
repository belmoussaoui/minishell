/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:54 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/18 13:13:45 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (!ft_isalnum(c) && !is_metachar(c) && c != '_'
		&& c != ' ' && c != '\\' && c != '$' && c != '"' && c != '\'');
}

void	check_wrong_seperators(t_data *data, char *line)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (line[i])
	{
		if (!check_quote(data, line[i]) && is_metachar(line[i]))
		{
			nb_pipe++;
			if (nb_pipe == 3 || (nb_pipe == 2 && !is_metachar(line[i - 1])))
			{
				werror(data, "syntax error near unexpected token `|'", 285);
				break ;
			}
			else if (line[i] == '|' && i != 0 && line[i - 1] == '<')
			{
				werror(data, "syntax error near unexpected token `|'", 285);
				break ;
			}
		}
		if (ft_isalnum(line[i]))
			nb_pipe = 0;
		i++;
	}
}

void	begin_end_with_separator(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (line[i] == '|')
		werror(data, "syntax error near unexpected token `|'", 285);
	i = ft_strlen(line) - 1;
	if (line[i] == '<' || line[i] == '>')
		werror(data, "syntax error near unexpected token `newline'", 285);
	i = 0;
	while (line[i])
	{
		if (is_special_char(line[i]))
			werror(data, "not a valid identifier", 1);
		i++;
	}
}

int	syntax_error(t_data *data)
{
	check_wrong_seperators(data, data->line);
	if (check_quote(data, 'c'))
		werror(data, "syntax error near unexpected token `quote'", 285);
	clear_quote(data);
	begin_end_with_separator(data, data->line);
	if (data->error_code)
		return (0);
	return (1);
}
