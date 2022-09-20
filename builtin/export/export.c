/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:29 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/20 16:28:43 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_export(t_data *data)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		printf("declare -x ");
		printf("%s", env_clone->name);
		if (env_clone->value && ft_strlen(env_clone->value))
			printf("=\"%s\"", env_clone->value);
		printf("\n");
		env_clone = env_clone->next;
	}
}

int	valid_name(char *name, t_data **data)
{
	if ((name[0] > 32 && name[0] < 65) || name[0] == '\0')
	{
		printf("bash: export: `%s': not a valid identifier\n", name);
		(*data)->exit_stat = 1;
		return (0);
	}
	return (1);
}

int	ft_export_arg(t_data *data, t_cmd *lst_cmd, char *name, char *value)
{
	int		i;

	i = 1;
	while (lst_cmd->cmd[i])
	{
		if (ft_name_exists(data, name))
			ft_change_env_value(data, name, value);
		else
		{
			if (valid_name(name, &data))
			{
				ft_add_new_env(data, name, value);
				if (!data->first_export)
					data->first_export = ft_substr(name, 0, ft_strlen(name));
				free(name);
				free(value);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_data *data, t_cmd *lst_cmd)
{
	char	*name;
	char	*value;

	if (lst_cmd && !lst_cmd->cmd[1])
	{
		ft_sort_env(data);
		ft_print_export(data);
	}
	else
	{
		name = ft_get_name_exp(lst_cmd->cmd[1]);
		value = ft_get_value_exp(lst_cmd->cmd[1]);
		return (ft_export_arg(data, lst_cmd, name, value));
	}
	return (0);
}
