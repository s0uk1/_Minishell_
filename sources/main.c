
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
void	check_access(char *cmd, char *to_join, t_envlst *env)
{
	int	fd;

	fd = access(ft_strcat(to_join, &cmd[0]), F_OK & X_OK);
	if (fd == -1)
		perror("access() error");
	else 
		execve(ft_strcat(to_join, &cmd[0]),cmd,NULL);
	perror("execve() error");
	//free
	exit(127);
}

void	execute_com(t_envlst *env, t_data *data, t_cmd *lst_cmd)
{
	t_cmdex	*inst;
	int	i;

	i = 0;
	inst->cmd = lst_cmd->cmd;
	if (getcwd(inst->cwd, sizeof(inst->cwd)) == NULL)
		perror("getcwd() error");
	if (inst->cmd[0][0] == '/')
		check_access(inst->cmd,'\0',NULL);
	while (env)
	{
		if (ft_strcmp(env->val_name, "PATH") == 0)
		{
			if(env->val == NULL)
				check_access(inst->cmd, inst->cwd, NULL);
			else
			{
				inst->env = ft_split(env->val,':');
				while (inst->env[i])
					check_access(inst->cmd, inst->env[i], inst->env);
			}
		}
		env = env->next;
	}
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
	//execlp("/sbin/ping", "/sbin/ping", "google.com", NULL);
	//int	i = 0;
	t_envlst *lst = NULL;
	t_data	*data = NULL;
	t_cmd	*cmd_test;

	(void)argc;
	
	data->lst_cmd = cmd_test;
	cmd_test->cmd = av;
	env_lst(&lst,env);
	execute_com(lst, data, cmd_test);
	//while (lst)
	//{
	//	printf("NAME%s\n",lst->val_name);
	//	printf("VALUE%s\n",lst->val);
	//	lst = lst->next;
	//}
}
