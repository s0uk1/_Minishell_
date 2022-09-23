/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:27:12 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/23 16:44:16 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	go_back_minus(t_data *data)
{
	int	exit_stat;

	exit_stat = chdir(getenv("OLDPWD"));
	if (exit_stat)
		exit_stat = chdir(custom_getenv("OLDPWD", data->lst_env));
	if (exit_stat)
		return (perror("chdir() error:"), 1);
	printf("%s\n", getenv("OLDPWD"));
	return (exit_stat);
}

void	print_error(void)
{
	printf("cd: error retrieving current directory:");
	printf("getcwd:cannot access parent directories:");
	printf(" No such file or directory\n");
}

int	go_home(t_data *data, char *cwd)
{
	int	exit_stat;

	exit_stat = chdir(getenv("HOME"));
	if (exit_stat)
		exit_stat = chdir(custom_getenv("HOME", data->lst_env));
	if (exit_stat)
	{
		free(cwd);
		cwd = NULL;
		perror("HOME not set");
		return (1);
	}
	update_pwd(data, cwd);
	free(cwd);
	cwd = NULL;
	return (exit_stat);
}
