/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrondia <lrondia@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:24:04 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/16 17:01:07 by lrondia          ###   ########.fr       */
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

void	ft_export(t_data *data, t_list **new_env)
{
	int		i;
	int		arg_count;
	char	**value;
	char	**elem_split;

	arg_count = 1;
	while (data->elements[arg_count])
	{
		i = 0;
		elem_split = ft_split(data->elements[arg_count], '=');
		while (i < data->len_env)
		{
			value = ft_split((ft_lstget(*new_env, i))->content, '=');
			if (!ft_strncmp(elem_split[0], value[0], ft_strlen(elem_split[0])))
				break ;
			i++;
		}
		if (i == data->len_env)
			ft_lstadd_back(new_env, ft_lstnew(data->elements[arg_count]));
		arg_count++;
	}
}

void	run_builtin(t_data *data, char *cmd_name)
{
	if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(data, &data->new_env);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(data, &data->new_env);
}
