/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 15:19:28 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int argc, char *argv[], char *envp[])
{
	t_list			*new_env;
	t_environment	env;
	int				i;

	(void) argc;
	(void) argv;
	new_env = NULL;
	i = 0;
	while (envp[i] != 0)
	{
		ft_lstadd_back(&new_env, ft_lstnew(envp[i]));
		env.before = ft_split(new_env->content, '=')[0];
		env.after = ft_split(new_env->content, '=')[1];
		new_env = new_env->next;
		i++;
		// printf("Avant : %s\n", env.before);
		// printf("Apres : %s\n", env.after);
	}
	// if (ft_strncmp(argv[1], "export", 7) == 0)
	// {
	// 	//Creer fonction ici
	// }

}

// void ft_unsetenv(int argc, char *argv[], char *envp[])
// {
// 	int i;

// 	i = 0;
// 	if (ft_strncmp(argv[1], "unset", 6) == 0)
// 	{
// 		while (19)
// 		{
// 			ft_remove();
// 			i++;			
// 		}
// 	}
// }

// Intialize minishell data and setup the environment.
void	initializer(t_data *data, int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	data->commands = NULL;
	data->error_code = 0;
	printf("La valeur de %s est %s\n", argv[1], getenv(argv[1]));
	ft_env(argc, argv, envp);
}
