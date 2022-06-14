/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:56:58 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/13 20:26:56 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_list(t_list *commands)
{
	int	i;

	while (commands)
	{
		i = 0;
		while (((t_cmd *)(commands->content))->elements[i])
		{
			printf("%s\n", ((t_cmd *)(commands->content))->elements[i]);
			i++;
		}
		commands = commands->next;
	}
}
