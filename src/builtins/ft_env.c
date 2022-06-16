/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:52:55 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/16 17:58:13 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list **env)
{
	t_list	*copy;

	copy = *env;
	while (copy)
	{
		printf("%s\n", copy->content);
		copy = copy->next;
	}
}
