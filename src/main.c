/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/06 17:10:07 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	*line;
	t_list	*commands;

	(void) argc;
	(void) argv;
	commands = NULL;
	while (19)
	{
		line = readline("minishell$ ");
		add_history(line);
		init_list_cmd(line, commands);
		exec(&data, line, envp);
	}
	return (1);
}
