/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:15:23 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/16 15:40:42 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_pwd(t_data *data, t_cmd *lst_cmd)
{
	char	cwd[256];

	if (lst_cmd->cmd[0])
	{
		getcwd(cwd, sizeof(cwd));
		if (cwd == NULL)
			printf("%s\n",custom_getenv("PWD", data->lst_env));
		else
			printf("%s\n", cwd);
	}
	return (0);
}
