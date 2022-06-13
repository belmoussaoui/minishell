/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:03:03 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/13 03:58:35 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reads a command written by the user in the terminal
char	*reader(void)
{
	char	*line;

	line = readline("minishell$ ");
	add_history(line);
	return (line);
}
