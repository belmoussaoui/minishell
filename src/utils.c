/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:08:51 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/14 20:44:23 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
