/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/20 20:08:12 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void) argc;
	(void) argv;
	initializer(&data, envp);
	while (19)
	{
		data.line = reader(&data);
		if (!syntax_error(&data))
			continue ;
		parser(&data, &data.commands, data.line);
		expander(&data, data.commands);
		execute(&data, envp);
		clear(&data, data.line);
	}
	return (1);
}
