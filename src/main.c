/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/13 12:28:53 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	initializer(&data, argc, argv, envp);
	while (19)
	{
		// if (!parsing(&data, line))
		// 	continue ;
		data.line = reader();
		lexer(data.line, data.commands);
		parser(data.commands);
		expander(data.commands);
		execute(&data, data.line, envp);
		clear(&data, data.line);
	}
	return (1);
}
