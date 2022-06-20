/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:03:03 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/20 19:53:30 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a command written by the user in the terminal
char	*reader(t_data *data)
{
	char	*line;

	run_signals(1);
	line = readline("minishell$ ");
	add_history(line);
	data->error_code = 0;
	return (line);
}
