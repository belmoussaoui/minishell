/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:54 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/07 20:21:36 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_wrong_seperators(t_data *data, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_charset(line[i]) && j != 0
			&& (j != 1 || (line[i - 1] && !is_charset(line[i - 1]))))
		{
			werror(data, "syntax error near unexpected token `|'", 285);
			break ;
		}
		else if (is_charset(line[i]) && line[i - 1]
			&& is_charset(line[i - 1]) && line[i] != line[i - 1])
		{
			werror(data, "syntax error near unexpected token `|'", 285);
			break ;
		}
		if (ft_isalnum(line[i]))
			j = 0;
		if (is_charset(line[i]))
			j++;
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
}

int	parsing(t_data *data, char *line)
{
	check_wrong_seperators(data, line);
	begin_end_with_separator(data, line);
	if (data->error_code)
		return (0);
	return (1);
}
