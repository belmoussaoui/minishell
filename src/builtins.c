/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:24:04 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/16 17:57:44 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	return (!ft_strncmp(cmd_name, "unset", 6)
		|| !ft_strncmp(cmd_name, "export", 7));
}

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

void	ft_unset(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(data->elements[1], envp[i],
				ft_strlen(data->elements[1])) == 0)
			printf("ft_unset\n");
		i++;
	}
}

void	run_builtin(t_data *data, char *cmd_name, char *envp[])
{
	if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(data, envp);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(data, &data->new_env);
}
