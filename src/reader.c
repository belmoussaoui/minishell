/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:03:03 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/28 16:58:46 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a command written by the user in the terminal
char	*reader(t_data *data)
{
	char	*line;

	(void) data;
	run_signals(1);
	term_config();
	line = readline("minishell$ ");
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line == '\0')
		return (NULL);
	add_history(line);
	return (line);
}
