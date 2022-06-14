/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 19:05:03 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Intialize minishell data and setup the environment.
void	initializer(t_data *data, int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	data->commands = NULL;
	data->error_code = 0;
	data->s_quote = 0;
	data->d_quote = 0;
}
