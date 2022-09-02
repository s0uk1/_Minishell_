/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:52:05 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/02 14:03:00 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi(const char *str)
{
	int i;
	int n;
	int res;

	i = 0;
	res = 0; 
	n = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * n);
}

int	ft_isdigit(char *num)
{
	int i;
    
    i = 0;
    while (num[i])
    {      
        if (num[i] >= '0' && num[i] <= '9')
		    return (1);
	    i++;
    }
    return (0);
}

int my_exit(t_data *data ,t_cmd *lst_cmd)
{
    char **cmd;

    cmd = lst_cmd->cmd;
    
    if (!lst_cmd->next)
    {
        ft_putstr_fd("exit\n", fd);   
        if (cmd[1])
        {
            if (cmd[2])
                printf("bash: exit: too many arguments\n");
            else if(ft_isdigit(cmd[1]))
                return (ft_atoi(cmd[1]));
            else
            {
                printf("bash: exit: %s :numeric argument required\n", cmd[1]);
                return (255);
            }  
        }
        else
            return (0);
    }
    return (0);
}