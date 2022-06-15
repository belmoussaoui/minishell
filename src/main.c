/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/15 14:50:22 by bel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	initializer(&data, argc, argv, envp);
	while (19)
	{
		data.line = reader(&data);
		if (!syntax_error(&data))
			continue ;
		parser(&data.commands, data.line);
		expander(data.commands);
		execute(&data, envp);
		clear(&data, data.line);
	}
	return (1);
}
