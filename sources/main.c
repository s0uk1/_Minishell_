
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

void	execute_com(t_envlst *lst, char *command)
{
	char cwd[256];
	char **paths;
	int		fd;
	//travel through the list until i find the path variable 
	if (getcwd(cwd), sizeof(cwd) == NULL)
		perror("getcwd() error");
	while (lst)
	{
		if (ft_strcmp(lst->val_name, "PATH") == 0)
			paths = ft_split(lst->val,':');
		lst = lst->next;
	}
	while (paths)
	{
		fd = access(, F_OK);
		if (fd == -1)
			printf("found error\n");
		else 
			printf("no errors found\n");
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
	(void)av;
	(void)argc;
	env_lst(&lst,env);
	execute_com(lst);
	//while (lst)
	//{
	//	printf("NAME%s\n",lst->val_name);
	//	printf("VALUE%s\n",lst->val);
	//	lst = lst->next;
	//}
}
