
#include "../includes/minishell.h"

t_envlst *env_lst(t_envlst **lst, char **env)
{
	t_envlst	*new;
	char 	**env_lst;
	int	i = 0;
	while (env[i])
	{
		new = (t_envlst *)malloc(sizeof(t_envlst));
		if (!new)
			return (NULL);
		env_lst = ft_split(*env, '=');
		new->val_name = env_lst[0];
		new->val = env_lst[1];
		lst_add(lst,new);
		env++;		
	}
	return (*lst);
}
//a function to check if a command exists in path using access 
//current workung directory to be stored in a struct ig
void	check_access(t_data *data, char **cmd, int i)
{
	char	*path = NULL;
	int		fd;

	path = ft_strjoin(data->paths[i], "/");
	path = ft_strjoin(path, cmd[0]);
	fd = access(path, F_OK & X_OK);
	if (fd == -1)
		return;
	else
	{
		printf("path is %s\n", path);
		execve(path, cmd, data->env);
		perror("execve() error");
	}
	//free
	exit(127);
}

void	execution_2(t_data *data)
{
	int	i;
	char	**cmd;
	char	**paths;
	t_env	*lst_env;

	i = -1;
	cmd = data->lst_cmd->cmd;
	lst_env = data->lst_env;
	if (getcwd(data->cwd, sizeof(data->cwd)) == NULL)
		perror("getcwd() error");
	if (cmd[0][0] == '/')
		check_access(data,NULL,0);
		// check_access(cmd[0],NULL,NULL);
	while (lst_env->name)
	{
		if (ft_strcmp(lst_env->name, "PATH") == 0)
		{
			if(lst_env->value == NULL)
			{
				printf("unset PATH variable");
				check_access(data,cmd, i);
			}
			else
			{
				data->paths = ft_split(lst_env->value,':');
				paths = data->paths;
				while (paths[++i])
				{
					printf("path :%s\n",paths[i]);
					check_access(data, cmd, i);
				}
			}
		}
		lst_env = lst_env->next;
	}
	// free(data);
}

//void	built_in(t_data *data)
//{
//	t_cmd	p_list;
//	char	**spl_res;
//	t_envlst *lst;
//
//	p_list = data->lst_cmd;
//	lst = env_lst(&lst,env);
//	while (p_lst->cmd)
//	{
//		if ((ft_strcmp(p_list->cmd[0], "export") == 0 ) && !p_list->cmd[1])
//			//alphabetically sort env variables and cat with (declare -x)
//			if ((ft_strcmp(p_list->cmd[0], "export") == 0) && p_list->cmd[1])
//			{
//				new = (t_envlst *)malloc(sizeof(t_envlst));
//				if (!new)
//					return (NULL);
//				if (ft_strchr(p_list->cmd[1], '='))
//				{
//					spl_res= ft_split(*env, '=');
//					new->val_name = spl_res[0];
//					new->val = spl_res[1];
//					lst_add(&lst,	new);
//				}
//				else
//				{
//					new->val_name = p_list_>cmd[1];
//					lst_add(&lst, new);
//				} 
//
//			}
//	}
//}

int main(int argc , char **av , char **env)
{
	//int	i = 0;
	t_data		data = NULL;
	t_cmd		cmd_test = NULL;
	t_envlst	lst;

	(void)argc;
	
	data.env = env;
	cmd_test.cmd = av;
	data.lst_cmd = cmd_test;
	env_lst(&lst,env);
	data.lst_env = lst;
	execute_com(lst, &data, cmd_test);
}
