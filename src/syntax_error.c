/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:54 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/22 11:59:48 by lrondia          ###   ########.fr       */
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
