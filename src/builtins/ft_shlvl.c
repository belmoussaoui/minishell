/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakermad <hakermad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:40:24 by hakermad          #+#    #+#             */
/*   Updated: 2022/06/21 13:42:35 by hakermad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int  ft_strcmp(const char *s1, const char *s2)
// {
//  size_t  i;
//  i = 0;
//  while (s1[i] == s2[i])
//  {
//      if (s1[i] == '\0' && s2[i] == '\0')
//          return (0);
//      i++;
//  }
//  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }
// void *ft_memdel(void *ptr)
// {
//  if (ptr)
//  {
//      free(ptr);
//      ptr = NULL;
//  }
//  return (NULL);
// // }
// char        *get_env_name(char *dest, const char *src)
// {
//     int     i;
//     i = 0;
//     while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
//     {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
//     return (dest);
// }
// void    increment_shell_level(t_data *data)
// {
//     int     shell_level;
//     char    env_name[BUFF_SIZE];
//     char    *shlvl;
//     char    *shell_level_value;
//     shell_level_value = get_env(data->new_env, "SHLVL");
//     if (ft_strncmp(shell_level_value, "", ft_strlen(shell_level_value)) == 0)
//         return ;
//     shell_level = ft_atoi_1(shell_level_value) + 1;
//     while (data && data->new_env->next)
//     {
//         get_env_name(env_name, data->new_env->content);
//         if (ft_strncmp("SHLVL", env_name, 6) == 0)
//         {
//             shlvl = ft_itoa(shell_level);
//             data->new_env->content = ft_strjoin("SHLVL=", shlvl);
//             return ;
//         }
//         data->new_env = data->new_env->next;
//     }
// }