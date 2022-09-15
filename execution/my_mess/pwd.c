/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:15:23 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 13:21:43 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_pwd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;

	if (lst_cmd->cmd[0])
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			cwd = custom_getenv("PWD", data->lst_env);
			printf("%s\n", cwd);
		}
		else
			printf("%s\n", cwd);
	}
	return (0);
}
