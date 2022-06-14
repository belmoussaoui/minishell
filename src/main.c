/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 13:55:27 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	initializer(&data, argc, argv, envp);
	while (19)
	{
		data.line = reader();
		if (!syntax_error(&data))
			continue ;
		parser(data.commands, data.line);
		expander(data.commands);
		execute(&data, envp);
		clear(&data, data.line);
	}
	return (1);
}
