#include "../../minishell.h"

int	ft_check_concate(char *name)
{
	char	*temp;

	if (name[ft_strlen(name) - 1] == '+')
	{
		temp = ft_substr(name, 0, ft_strlen(name) - 1);
		free(name);
		name = ft_strdup(temp);
		free(temp);
		return (1);
	}
	return (0);
}

void	ft_new_export(t_data *data, char *name, char *value)
{
	ft_add_new_env(data, name, value);
	if (!data->first_export)
		data->first_export = ft_substr(name, 0, ft_strlen(name));
}

void	ft_change_prev_value(t_env *env, char *value)
{
	char	*temp;

	temp = NULL;
	temp = env->value;
	env->value = ft_strjoin(temp, value);
}

void	ft_concatenate(t_data *data, char *name, char *value)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (ft_name_exists(data, name))
	{
		while (env_clone)
		{
			if (!ft_strcmp(env_clone->name, name))
				ft_change_prev_value(env_clone, value);
			env_clone = env_clone->next;
		}
		free(name);
		free(value);
	}
	else
	{
		ft_new_export(data, name, value);
		if (name)
			free(name);
		if (value)
			free(value);
	}
}
