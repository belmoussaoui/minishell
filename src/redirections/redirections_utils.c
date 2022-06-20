/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:03:36 by lrondia           #+#    #+#             */
/*   Updated: 2022/06/20 19:00:13 by lrondia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file(char *line)
{
	int		i;
	char	*file;

	i = 0;
	file = ft_strdup(line);
	if (!file)	
		exit (EXIT_FAILURE);
	while (file[i] && file[i]!= '|')
		i++;
	if (file[i] == '|')
		file[i] = '\0';
	return (file);
}

void	write_stdin(char *stop, int file_id)
{
	char	*gnl;

	write(1, "> ", 2);
	gnl = get_next_line(0);
	while (gnl && !(!ft_strncmp(gnl, stop, ft_strlen(stop))
			&& ft_strlen(gnl) - 1 == ft_strlen(stop)))
	{
		write (file_id, gnl, ft_strlen(gnl));
		free (gnl);
		write(1, "> ", 2);
		gnl = get_next_line(0);
	}
	if (gnl)
		free (gnl);
}
