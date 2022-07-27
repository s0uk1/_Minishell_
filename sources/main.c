
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

int main(int argc , char **av , char **env)
{
	//execlp("/sbin/ping", "/sbin/ping", "google.com", NULL);
	//int	i = 0;
	t_envlst *lst = NULL;
	(void)av;
	(void)argc;
	env_lst(&lst,env);
	while (lst)
	{
		printf("NAME%s\n",lst->val_name);
		printf("VALUE%s\n",lst->val);
		lst = lst->next;
	}
}
