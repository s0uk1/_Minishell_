/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/20 16:28:32 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_chdir(t_data *data, char *cmd, char *cwd)
{
	char	*new_pwd;

	data->exit_stat = chdir(cmd);
	if (data->exit_stat)
		return (perror("chdir() error:"), 1);
	else
	{
		new_pwd = getcwd(NULL, 256);
		update_env(data, "OLDPWD", cwd);
		update_env(data, "PWD", new_pwd);
	}
	free(new_pwd);
	return (data->exit_stat);
}

void	find_dir(t_data *data, char *pwd, char *upd)
{
	int		i;
	char	*test_pwd;

	i = 0;
	test_pwd = NULL;
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	test_pwd = ft_strncpy(test_pwd, pwd, i);
	if (chdir(test_pwd))
		find_dir(data, test_pwd, upd);
	else
		my_chdir(data, test_pwd, upd);
	free(test_pwd);
}
// int	catch_error(t_data *data)
// {
// 	char	*old_pwd;
// 	char	*new_pwd;
// 	char	*free_pwd;
// 	char	*free_join;

// 	old_pwd = custom_getenv("PWD", data->lst_env);
// 	printf("|||||%s||||||\n",old_pwd);
// 	printf("cd: error retrieving current directory:");
// 	printf("getcwd:cannot access parent directories:");
// 	printf(" No such file or directory\n");
// 	free_join = cd_strjoin(old_pwd, "/..");
// 	printf("|||||%s||||||\n",old_pwd);
// 	update_env(data, "PWD", free_join);
// 	printf("|||||%s||||||\n",old_pwd);
// 	update_env(data, "OLDPWD", old_pwd);
// 	printf("|||||%s||||||\n",old_pwd);
// 	printf("|||||%s||||||\n",old_pwd);
// 	free_pwd = ft_strdup(old_pwd);
// 	printf("|||||%s||||||\n",old_pwd);
// 	old_pwd = cd_strjoin(free_pwd, "/..");
// 	printf("|||||%s||||||\n",old_pwd);
// 	data->exit_stat = chdir(old_pwd);
// 	if (data->exit_stat)
// 		find_dir(data, old_pwd, old_pwd);
// 	free(free_pwd);
// 	free(old_pwd);
// 	return (data->exit_stat);
// }
int	catch_error(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*free_pwd;
	char	*join_pwd;

	old_pwd = custom_getenv("PWD", data->lst_env);
	printf("cd: error retrieving current directory:");
	printf("getcwd:cannot access parent directories:");
	printf(" No such file or directory\n");
	join_pwd = cd_strjoin(old_pwd, "/..");
	update_env(data, "PWD", join_pwd);
	update_env(data, "OLDPWD", old_pwd);
	free_pwd = ft_strdup(old_pwd);
	old_pwd = cd_strjoin(free_pwd, "/..");
	data->exit_stat = chdir(old_pwd);
	if (data->exit_stat)
		find_dir(data, old_pwd, old_pwd);
	free(free_pwd);
	free(old_pwd);
	return (data->exit_stat);
}

int	my_cd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;
	char	**cmd;
	int		exit_stat;

	cmd = lst_cmd->cmd;
	cwd = getcwd(NULL, 256);
	if (cmd[1])
	{
		if (!cwd)
			return (catch_error(data));
		else
			exit_stat = my_chdir(data, cmd[1], cwd);
	}
	else
	{
		exit_stat = chdir(custom_getenv("HOME", data->lst_env));
		if (exit_stat)
		{
			free(cwd);
			return (perror("chdir() error:"), 1);
		}
		update_pwd(data, cwd);
	}
	free(cwd);
	return (exit_stat);
}
