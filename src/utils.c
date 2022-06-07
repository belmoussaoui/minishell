/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:08:51 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/07 19:54:32 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	werror(t_data *data, char *message, int code)
{
	int	len;

	len = ft_strlen(message);
	data->error_code = code;
	write(2, message, len);
	write(2, "\n", 1);
}

void	werror_exit(t_data *data, char *message, int code)
{
	int	len;

	len = ft_strlen(message);
	data->error_code = code;
	write(2, message, len);
	write(2, "\n", 1);
	exit(code);
}
