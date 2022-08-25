/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/25 16:24:04 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../debug.h"

// what i need in cd is 
// updating PWD var whenever i change the directory
// in the case of nested directories , if i cd to the last one 
// then delete one of the previous ones i have to implement 
// a workaround to avoid painful segfauls

//i should check for deleted nested directories using cwd 
//if it fails i then append .. and change env vars
void    update_env(t_data *data, char *env, char *upd)
{
    t_env *lst;

    lst = data->lst_env;
    while(lst)
    {
        if (!ft_strcmp(lst->name, env))
        {
            lst->value = ft_strdup(upd);
            break ;
        }
        lst = lst->next;
    }  
}
 
void    buff_chdir(t_data *data, char **cmd, char *cwd)
{
    char *new_pwd;
    
    new_pwd = NULL;
    if (!cmd[1])
    {
        if (chdir(custom_getenv("HOME", data->lst_env)))
            perror("chdir() error:");
    }
    else
    {
        if (chdir(cmd[1]))
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
    // perror("cd() error:");
    char *old_pwd;
    
    old_pwd = custom_getenv("PWD", data->lst_env);
    printf("cd: error retrieving current directory: getcwd:cannot access parent directories: No such file or directory\n");
    update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
    update_env(data, "OLD_PWD", old_pwd);
    if (chdir(ft_strjoin(old_pwd, "/..")))
        perror("chdir() error:");
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
            buff_chdir(data , cmd, cwd);   
        // if (chdir(cmd[1]))
        //     perror("chdir() error:");
        // else
        //     update_env("PWD");
    }
}