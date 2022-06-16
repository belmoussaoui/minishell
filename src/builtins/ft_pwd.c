/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:38:03 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/16 18:58:09 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*direction;

	direction = NULL;
	direction = getcwd(direction, 0);
	if (!direction)
		printf("Error pwd\n");
	printf("%s test\n", direction);
	free(direction);
	return (0);
}
