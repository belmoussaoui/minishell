/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:56:58 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/23 17:48:40 by lrondia          ###   ########.fr       */
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

void	debug_split(char **split)
{
	int	i;

	i = 0;
	printf("--------------------------\n");
	while (split[i])
	{
		printf("debug --> %s\n", split[i]);
		i++;
	}
}
