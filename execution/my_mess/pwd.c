/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:15:23 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/17 18:57:17 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_pwd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;

	if (lst_cmd->cmd[0])
	{
		cwd = getcwd(NULL, 256);
		if (cwd == NULL)
			printf("%s\n",custom_getenv("PWD", data->lst_env));
		else
		{
			printf("%s\n", cwd);
			free(cwd);
		}
	}
	return (0);
}
