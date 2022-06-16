/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 04:01:14 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 20:37:29 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear(t_data *data, char *line)
{
	data->commands = NULL;
	data->s_quote = 0;
	data->d_quote = 0;
	free(line);
}
