/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:03:03 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/22 15:50:51 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a command written by the user in the terminal
char	*reader(t_data *data)
{
	char	*line;

	run_signals(1);
	line = readline("minishell$ ");
	// system("leaks minishell");
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	add_history(line);
	data->error_code = 0;
	return (line);
}
