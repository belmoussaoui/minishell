/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:03:03 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/24 16:58:12 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a command written by the user in the terminal
char	*reader(t_data *data)
{
	char	*line;

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
	data->error_code = 0;
	return (line);
}
