/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/28 12:02:37 by hakermad         ###   ########.fr       */
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
		if (!data.line || !syntax_error(&data) || is_only_space(data.line))
			continue ;
		parser(&data, &data.commands, data.line);
		expander(&data, data.commands);
		execute(&data);
		clear(&data);
	}
	return (1);
}
