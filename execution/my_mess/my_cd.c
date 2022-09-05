/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/05 17:03:39 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
        }
        lst = lst->next;
    }
    return (NULL);    
}

char *custom_getenv(char *env_var, t_env *env_lst)
{
	t_env *tmp;
	char *pwd;
	
	tmp = env_lst;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, env_var))
		{
			pwd = tmp->value;
			break;
		}
		else
			tmp = tmp->next;
	}
	return (pwd);
}

 int    my_chdir(t_data *data, char *cmd, char *cwd)
{
    char *new_pwd;
    
    new_pwd = NULL;
    if (!cmd)
    {
        data->exit_stat = chdir(custom_getenv("HOME", data->lst_env));
        if (data->exit_stat)
            return (perror("chdir() error:"),1);
    }
    else
    {
        data->exit_stat = chdir(cmd);
        if (data->exit_stat)
            return (perror("chdir() error:"),1);    
        else
        {
            new_pwd = getcwd(NULL, 0);
            update_env(data, "OLDPWD", cwd);
            update_env(data, "PWD", new_pwd);
        }     
    }
    return (data->exit_stat);           
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
    dest = (char *)malloc(sizeof(char) * n + 1);
	while ((src[i] != '\0') && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void    find_dir(t_data *data, char *pwd, char *upd)
{
    int     i;
    char    *test_pwd;

    i = 0;
    while(pwd[i])
        i++;
    while (pwd[i] != '/')
        i--;   
    test_pwd = ft_strncpy(test_pwd, pwd, i);
    if (chdir(test_pwd))
        find_dir(data ,test_pwd, upd);
    else
    {
        printf("%s\n",upd);
        my_chdir(data, test_pwd, upd);
    }
}

//this function replicates the behavior of bash when
// a nested directory is deleted
//the last if in this function goes back in nested dirs
//checking for the working one and updating env accordingly
int catch_error(t_data *data)
{
    char    *old_pwd;
    char    *new_pwd;
    
    old_pwd = custom_getenv("PWD", data->lst_env);
    printf("cd: error retrieving current directory:");
    printf("getcwd:cannot access parent directories:");
    printf(" No such file or directory\n"); 
    update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
    new_pwd = update_env(data, "OLDPWD", old_pwd);
    old_pwd = ft_strjoin(old_pwd, "/..");
    data->exit_stat = chdir(old_pwd);
    if (data->exit_stat)
        find_dir(data, old_pwd, old_pwd);
    return (data->exit_stat);
}



// if !cwd means that there was an error while executing getcwd
// meaning that one directory got deleted
int my_cd(t_data *data, t_cmd *lst_cmd)
{
    char *cwd;
    char **cmd;
    
    cmd = lst_cmd->cmd;
    cwd = getcwd(NULL, 0);
    if (cmd[1])
    {
        if (!cwd)
            data->exit_stat = catch_error(data);
        else
            return(my_chdir(data , cmd[1], cwd));   
    }
    return (data->exit_stat);
}