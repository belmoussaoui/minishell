/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:05:53 by bel-mous          #+#    #+#             */
/*   Updated: 2022/06/14 18:20:48 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_export(int argc, char *argv[], t_list **new_env)
// {
// 	(void) argc;

// 	if (ft_strncmp(argv[1], "export", 7) == 0)
// 	{
// 		ft_lstadd_back(new_env, ft_lstnew(argv[2]));
// 	}
// }

// void	ft_unset(t_environment *environment, char **str, int argc, char *argv[])
// {
// 	t_environment	*current;
// 	t_environment	*temp;
// 	int				i;

// 	(void) argc;
// 	current = environment;
// 	i = 0;

// 	if (ft_strncmp(argv[1], "unset", 6) == 0)
// 	{
// 		if (current->content)
// 		{
// 			temp = current->next;
// 			*current = *temp;
// 		}
// 		printf("ok");
// 	}
	
// }

void	ft_env(int argc, char *argv[], char *envp[])
{
	t_list			*new_env;
	t_environment	env;
	int				i;

	(void) argc;
	(void) argv;
	new_env = NULL;
	i = 0;
	
	//ft_export(argc, argv, &new_env);
	while (envp[i] != 0)
	{
		ft_lstadd_back(&new_env, ft_lstnew(envp[i]));
		env.before = ft_split(new_env->content, '=')[0];
		env.after = ft_split(new_env->content, '=')[1];
		new_env = new_env->next;
		printf("Avant : %s\n", env.before);
		printf("Apres : %s\n", env.after);
		i++;
	}
	//printf("%s\n", new_env->content);

}


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
