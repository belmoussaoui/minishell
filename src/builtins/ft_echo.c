/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:20:33 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/21 20:38:49 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_echo(t_data *data)
{
	int	i;

	if (!data->elements || ft_strcmp("echo", *data->elements))
		return (true);
	i = 1;
	while (data->elements[i])
	{
		if (ft_strcmp(data->elements[1], "-n") || i > 1)
			printf("%s", data->elements[i]);
		if (data->elements[i + 1] && ft_strcmp(data->elements[i], "-n"))
			printf(" ");
		i++;
	}
	if (ft_strcmp(data->elements[1], "-n"))
		printf("\n");
	return (false);
}
