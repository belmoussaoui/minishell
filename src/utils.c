/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:08:51 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/13 19:33:37 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
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
