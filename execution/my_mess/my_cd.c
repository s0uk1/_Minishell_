/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/25 18:24:24 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../debug.h"


char *update_env(t_data *data, char *env, char *upd)
{
    t_env *lst;

    lst = data->lst_env;
    while(lst)
    {
        if (!ft_strcmp(lst->name, env))
        {
            lst->value = ft_strdup(upd);
            return (lst->value);
            // break ;
        }
        lst = lst->next;
    }
    return (NULL);    
}
 
void    buff_chdir(t_data *data, char *cmd, char *cwd)
{
    char *new_pwd;
    
    new_pwd = NULL;
    if (!cmd)
    {
        if (chdir(custom_getenv("HOME", data->lst_env)))
            perror("chdir() error:");
    }
    else
    {
        if (chdir(cmd))
            perror("chdir() error:");    
        else
        {
            new_pwd = getcwd(NULL, 0);
            update_env(data, "OLDPWD", cwd);
            update_env(data, "PWD", new_pwd);
        }     
    }
            
}

void    catch_error(t_data *data)
{
    char    *old_pwd;
    char    *new_pwd;
    
    old_pwd = custom_getenv("PWD", data->lst_env);
    printf("cd: error retrieving current directory: getcwd:cannot access parent directories: No such file or directory\n");
    update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
    new_pwd = update_env(data, "OLDPWD", old_pwd);
    if (chdir(ft_strjoin(old_pwd, "/..")))
        buff_chdir(data, custom_getenv("HOME", data->lst_env), new_pwd);
}

void    my_cd(t_data *data, t_cmd *lst_cmd)
{
    char *cwd;
    char **cmd;
    
    cmd = lst_cmd->cmd;
    cwd = getcwd(NULL, 0);
    if (cmd[1])
    {
        if (!cwd)
            catch_error(data);
        else
            buff_chdir(data , cmd[1], cwd);   
        // if (chdir(cmd[1]))
        //     perror("chdir() error:");
        // else
        //     update_env("PWD");
    }
}