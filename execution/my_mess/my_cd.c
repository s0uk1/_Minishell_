/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/26 18:35:14 by ssabbaji         ###   ########.fr       */
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
 
void    my_chdir(t_data *data, char *cmd, char *cwd)
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

// char	*ft_strchr(const char *str, int c)
// {
// 	size_t		i;
// 	size_t		size;

// 	i = 0;
// 	size = ft_strlen(str);
// 	while (i < size)
// 	{
// 		if (str[i] == (char )c)
// 			return ((char *)(str + i));
// 		i++;
// 	}
// 	if (c == '\0')
// 		return ((char *)(str + i));
// 	return (NULL);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	start;
// 	size_t	end;
// 	char	*str;

// 	str = 0;
// 	if (s1 != 0 && set != 0)
// 	{
// 		start = 0;
// 		end = ft_strlen(s1);
// 		while (s1[start] && ft_strchr(set, s1[start]))
// 			start++;
// 		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
// 			end--;
// 		str = (char *)malloc(sizeof(char) * (end - start + 1));
// 		if (str)
// 			ft_strlcpy(str, &s1[start], end - start + 1);
// 	}
// 	return (str);
// }

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
void    catch_error(t_data *data)
{
    char    *old_pwd;
    char    *new_pwd;
    
    old_pwd = custom_getenv("PWD", data->lst_env);
    printf("cd: error retrieving current directory: getcwd:cannot access parent directories: No such file or directory\n");
    update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
    new_pwd = update_env(data, "OLDPWD", old_pwd);
    old_pwd = ft_strjoin(old_pwd, "/..");
    if (chdir(old_pwd))
        find_dir(data, old_pwd, old_pwd);
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
            my_chdir(data , cmd[1], cwd);   
        // if (chdir(cmd[1]))
        //     perror("chdir() error:");
        // else
        //     update_env("PWD");
    }
}