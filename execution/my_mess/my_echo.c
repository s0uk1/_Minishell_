/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:42:26 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/08/28 14:00:54 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_cmd(char **argv, int argc, int flag)
{
	int		i;
	char	*args;

    if (!flag)
        i = 2;
    else
	    i = 1;
	args = NULL;
	while (i < argc)
	{
		args = ft_strjoin(args, argv[i++]);
		args = ft_strjoin(args, " ");
	}
	return (args);
}
////////////////////////////////////////////////

int my_strchr(char *str, int c)
{
	size_t		i;
	size_t		size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (str[i] == (char )c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int    check_valid(char *cmd)
{
    char *tmp;
    int i;

    i = 1;
    tmp = cmd;
    while (tmp[i])
    {
        if (tmp[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void    print_rest(char **cmd, int i, int flag)
{
    char *echo;
    if (!flag)
    {
       echo = join_cmd(cmd, count_cmds(cmd), 0);
       echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
       printf("%s",echo);
    }
    if (flag)
    {
        echo = join_cmd(cmd, count_cmds(cmd), 1);
        echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
        printf("%s",echo);
        printf("\n");
    }
}


void    my_echo(t_data *data ,t_cmd *lst_cmd)
{
    char **cmd;
    int i;
    int j;

    i = 1;
    j = 0;
    cmd = lst_cmd->cmd;
    while (cmd[i])
    {
        if (cmd[i][0] == '-' && cmd[i][1] == 'n')
        {
            if (!check_valid(cmd[i]))
            {
                print_rest(cmd, i, 0);
                break ;       
            }    
        } 
        i++;
    }
    i = 1;
    if (cmd[i][0] == '-' && cmd[i][1] == 'n')
        print_rest(cmd, 2, 0);
    else
        print_rest(cmd, 1, 1);  
}


