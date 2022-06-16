/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:56:58 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/15 19:51:58 by hakermad         ###   ########.fr       */
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

void	debug_env(t_list *env)
{
	while (env)
	{
		printf("debug --> %s\n", env->content);
		env = env->next;
	}
}
