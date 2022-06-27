/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:13:54 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/27 20:48:16 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_s_error(t_data *data, char c, char *s, int code)
{
	data->error_code = code;
	write(2, "syntax error near unexpected token `", 36);
	if (c)
		write(2, &c, 1);
	else
		write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
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
			if (nb_pipe == 3 || (nb_pipe == 2 && !is_metachar(line[i])))
			{
				print_s_error(data, line[i], 0, 285);
				break ;
			}
			else if (line[i] == '|' && i != 0 && line[i - 1] == '<')
			{
				print_s_error(data, line[i], 0, 285);
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
	int		max;
	char	*str;
	char	**split;

	if (data->error_code)
		return ;
	split = ft_split(line, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	str = join_the_split(split);
	if (line[0] == '|')
		print_s_error(data, line[0], 0, 285);
	max = ft_strlen(str) - 1;
	if (str[max] == '<' || str[max] == '>')
		print_s_error(data, 0, "newline", 285);
	else if (str[max - 1] && (str[max - 1] == '<' || str[max - 1] == '>'))
		print_s_error(data, str[max], 0, 285);
	free_split(split);
}

int	syntax_error(t_data *data)
{
	int	save;

	save = data->error_code;
	data->error_code = 0;
	check_wrong_seperators(data, data->line);
	if (check_quote(data, 'c'))
		werror(data, "syntax error near unexpected token `quote'", 285);
	clear_quote(data);
	begin_end_with_separator(data, data->line);
	if (data->error_code == 285)
		return (0);
	data->error_code = save;
	return (1);
}
