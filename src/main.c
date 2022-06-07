/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/07 19:50:17 by lrondia          ###   ########.fr       */
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
		if (!parsing(&data, line))
			continue ;
		init_list_cmd(line, commands);
		exec(&data, line, envp);
	}
	return (1);
}
