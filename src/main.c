/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliban-s <mliban-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:20 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/02 13:34:34 by mliban-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (19)
	{
		line = readline("minishell$ ");
		add_history(line);
		printf("%s\n", line);
		ft_split(" ",*line);
	}
	return (1);
}
