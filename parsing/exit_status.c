/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:59 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/30 14:46:24 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_allocate(char *exit, char *value)
{
	int		len;
	char	*new;

	len = ft_strlen(exit) + ft_strlen(value) - 2;
	new = malloc(sizeof(char) * len - 1);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_new_value(t_data *data, char *value)
{
	char	*new_value;
	int		i;
	int		j;
	char	*temp;

	j = 0;
	i = 0;
	temp = ft_itoa(data->general.old_error);
	new_value = ft_allocate(temp, value);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			new_value = ft_strjoin(new_value, temp);
			j += ft_strlen(temp);
			i += 2;
		}
		else
		{
			new_value[j] = value[i];
			j++;
			i++;
		}
	}
	free(temp);
	new_value[j] = '\0';
	return (new_value);
}

char	*ft_change_value(t_data *data, char *value)
{
	char	*temp;

	temp = ft_substr(value, 0, ft_strlen(value));
	free(value);
	value = ft_new_value(data, temp);
	free(temp);
	return (value);
}

void	ft_change_exit_status(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		data->flag_d = 0;
		data->flag_s = 0;
		i = 0;
		while (lexer_clone->val[i])
		{
			if (lexer_clone->val[i] == '"' && data->flag_s == 0)
				ft_change_flag(data->flag_d);
			if (lexer_clone->val[i] == '\'' && data->flag_d == 0)
				ft_change_flag(data->flag_s);
			if (data->flag_s == 0 && lexer_clone->val[i] == '$'
				&& lexer_clone->val[i + 1] == '?')
				lexer_clone->val = ft_change_value(data, lexer_clone->val);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
}
