/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/17 16:08:52 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// t_data 	*update_pwd(t_data *data, char *cwd)
// {
// 	char new_pwd[256];
	
// 	getcwd(new_pwd, sizeof(new_pwd));
// 	update_env(data, "OLDPWD", cwd);
// 	update_env(data, "PWD", new_pwd);
// 	return (data);
// }

// int	my_chdir(t_data *data, char *cmd, char *cwd)
// {
// 	char	*new_pwd;

// 	new_pwd = NULL;

// 	data->exit_stat = chdir(cmd);
// 	if (data->exit_stat)
// 		return (perror("chdir() error:"), 1);
// 	else
// 	{
// 		new_pwd = getcwd(NULL, 0);
// 		update_env(data, "OLDPWD", cwd);
// 		update_env(data, "PWD", new_pwd);
// 	}
// 	// free(new_pwd);
// 	//this shouldnt be here double free
// 	return (data->exit_stat);
// }

// void	find_dir(t_data *data, char *pwd, char *upd)
// {
// 	int		i;
// 	char	*test_pwd;

// 	i = 0;
// 	while (pwd[i])
// 		i++;
// 	while (pwd[i] != '/')
// 		i--;
// 	test_pwd = ft_strncpy(test_pwd, pwd, i);
// 	if (chdir(test_pwd))
// 		find_dir(data, test_pwd, upd);
// 	else
// 	{
// 		printf("%s\n", upd);
// 		my_chdir(data, test_pwd, upd);
// 	}
// }

// int	catch_error(t_data *data)
// {
// 	char	*old_pwd;
// 	char	*new_pwd;

// 	old_pwd = custom_getenv("PWD", data->lst_env);
// 	printf("cd: error retrieving current directory:");
// 	printf("getcwd:cannot access parent directories:");
// 	printf(" No such file or directory\n");
// 	update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
// 	new_pwd = update_env(data, "OLDPWD", old_pwd);
// 	old_pwd = ft_strjoin(old_pwd, "/..");
// 	data->exit_stat = chdir(old_pwd);
// 	if (data->exit_stat)
// 		find_dir(data, old_pwd, old_pwd);
// 	// free(old_pwd);
// 	// free(new_pwd);
// 	return (data->exit_stat);
// }

// // int	my_cd(t_data *data, t_cmd *lst_cmd)
// // {
// // 	char	cwd[256];
// // 	char	**cmd;

// // 	cmd = lst_cmd->cmd;
// // 	getcwd(cwd, sizeof(cwd));
// // 	printf("%s\n",cwd);
// // 	if (cmd[1])
// // 	{
// // 		if (cwd == NULL)
// // 			data->exit_stat = catch_error(data);
// // 		else
// // 			return (my_chdir(data, cmd[1], cwd));
// // 	}
// // 	else
// // 	{
// // 		data->exit_stat = chdir(custom_getenv("HOME", data->lst_env));
// // 		if (data->exit_stat)
// // 			return (perror("chdir() error:"), 1);
// // 		update_pwd(data, cwd);
// // 	}
// // 	return (data->exit_stat);
// // }

// int	my_cd(t_data *data, t_cmd *lst_cmd)
// {
// 	char	*cwd;
// 	char	**cmd;
// 	int		exit_stat;

	
// 	cmd = lst_cmd->cmd;
// 	if (cmd[1])
// 	{
// 		cwd = getcwd(NULL, 256);
// 		if (cwd == NULL)
// 			exit_stat = catch_error(data);
// 		else
// 		{
// 			exit_stat = my_chdir(data, cmd[1], cwd);
// 			free(cwd);
// 		}
// 	}
// 	else
// 	{
// 		exit_stat = chdir(custom_getenv("HOME", data->lst_env));
// 		if (exit_stat)
// 			return (perror("chdir() error:"), 1);
// 		update_pwd(data, cwd);
// 	}
// 	// free(cwd);
// 	return (exit_stat);
// }


t_data 	*update_pwd(t_data *data, char *cwd)
{
	char new_pwd[256];
	
	getcwd(new_pwd, sizeof(new_pwd));
	update_env(data, "OLDPWD", cwd);
	update_env(data, "PWD", new_pwd);
	return (data);
}


// int	my_chdir(t_data *data, char *cmd, char *cwd)
// {
// 	data->exit_stat = chdir(cmd);
// 	if (data->exit_stat)
// 		return (perror("chdir() error:"), 1);
// 	else
// 		update_pwd(data, cwd);
// 	return (data->exit_stat);
// }

// void	find_dir(t_data *data, char *pwd, char *upd)
// {
// 	int		i;
// 	char	*test_pwd;

// 	i = 0;
// 	while (pwd[i])
// 		i++;
// 	while (pwd[i] != '/')
// 		i--;
// 	test_pwd = ft_strncpy(test_pwd, pwd, i);
// 	if (chdir(test_pwd))
// 		find_dir(data, test_pwd, upd);
// 	else
// 	{
// 		printf("%s\n", upd);
// 		my_chdir(data, test_pwd, upd);
// 	}
// }

// int	catch_error(t_data *data)
// {
// 	char	*old_pwd;
// 	char	*new_pwd;

// 	old_pwd = custom_getenv("PWD", data->lst_env);
// 	printf("cd: error retrieving current directory:");
// 	printf("getcwd:cannot access parent directories:");
// 	printf(" No such file or directory\n");
// 	update_env(data, "PWD", ft_strjoin(old_pwd, "/.."));
// 	new_pwd = update_env(data, "OLDPWD", old_pwd);
// 	old_pwd = cd_strjoin(old_pwd, "/..");
// 	data->exit_stat = chdir(old_pwd);
// 	if (data->exit_stat)
// 		find_dir(data, old_pwd, old_pwd);
// 	return (data->exit_stat);
// }

// int	expand_tilde(t_data *data, char **cmd, char *cwd)
// {
// 	return (0);
// }

// int	my_cd(t_data *data, t_cmd *lst_cmd)
// {
// 	char	*cwd;
// 	char	**cmd;

// 	cmd = lst_cmd->cmd;
// 	cwd = getcwd(NULL, 0);
// 	if (cmd[1])
// 	{
// 		if (!cwd)
// 			data->exit_stat = catch_error(data);
// 		else
// 			return (my_chdir(data, cmd[1], cwd));
// 	}
// 	else if (cmd[1][0] == '~')
// 		data->exit_stat = expand_tilde(data, cmd, cwd);
// 	else if (!cmd[1])
// 	{
// 		data->exit_stat = chdir(custom_getenv("HOME", data->lst_env));
// 		if (data->exit_stat)
// 			return (perror("chdir() error:"), 1);
// 		update_pwd(data, cwd);
// 	}
// 	free(cwd);
// 	return (data->exit_stat);
// }


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

int	catch_error(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*free_pwd;
	char	*free_join;

	old_pwd = custom_getenv("PWD", data->lst_env);
	printf("cd: error retrieving current directory:");
	printf("getcwd:cannot access parent directories:");
	printf(" No such file or directory\n");
	free_join =  cd_strjoin(old_pwd, "/..");
	update_env(data, "PWD", free_join);
	free(free_join);
	update_env(data, "OLDPWD", old_pwd);
	free_pwd = old_pwd;
	old_pwd = cd_strjoin(old_pwd, "/..");
	free(free_pwd);
	data->exit_stat = chdir(old_pwd);
	if (data->exit_stat)
		find_dir(data, old_pwd, old_pwd);
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
			return(catch_error(data));
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