/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:26 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/26 17:22:08 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_value_before(t_data *data, int i, char *value)
{
	i = 0;
	data->flag_s = 0;
	data->flag_d = 0;
	while (data->flag_s == 1 || (value[i] && value[i] != '$'))
	{
		if (value[i] == '"' && data->flag_s == 0)
			data->flag_d = ft_change_flag(data->flag_d);
		if (value[i] == '\'' && data->flag_d == 0)
			data->flag_s = ft_change_flag(data->flag_s);
		i++;
	}
	return (i);
}

int	ft_value_var(int i, char *value)
{
	while (value[i] && !ft_isspace(value[i]) && value[i] != '$'
		&& value[i] != '\\' && value[i] != '"'
		&& value[i] != '\'' && value[i] != '='
		&& value[i] != '+'
		&& value[i] != '-'
		&& value[i] != '/'
		&& value[i] != '%')
		i++;
	return (i);
}

char	*generate_nv(char *lexer_val)
{
	char	*temp;
	char	*n_v;

	temp = NULL;
	n_v = NULL;
	temp = ft_substr(lexer_val, 0, ft_len_before(lexer_val));
	n_v = ft_strjoin(n_v, temp);
	return (n_v);
}

void	ft_real_expanding(t_data *data, t_lexer *lexer, char *var, char *n_v)
{
	int		i;
	// char	*free_nv;

	i = 0;
	n_v = generate_nv(lexer->val);
	// free_nv = n_v;
	// free(free_nv);
	i = ft_value_before(data, i, lexer->val);
	if (lexer->val[i] && lexer->val[i + 1])
		var = ft_substr(lexer->val, i + 1, ft_len_var(lexer->val));
	if (var)
	{
		if (ft_check_var_env(data, var))
		{
			n_v = ft_strjoin(n_v, ft_get_value(data, var));
			i++;
			i = ft_value_var(i, lexer->val);
			if (lexer->val[i])
				n_v = ft_fix_norme(n_v, lexer->val, i);
		}
		else
			n_v = ft_strjoin(n_v, ft_delete_var(data, lexer->val));
		lexer->val = ft_change_nd_free(lexer->val, var, n_v);
	}
}

void	ft_expanding(t_data *data)
{
	t_lexer	*lexer_clone;
	char	*var;
	char	*new_var;

	new_var = NULL;
	lexer_clone = data->lst_lexer;
	while (ft_check_still_dollar(data))
	{
		lexer_clone = data->lst_lexer;
		while (lexer_clone)
		{
			if (!ft_strcmp(lexer_clone->val, "<<"))
			{
				lexer_clone = lexer_clone->next;
				if (lexer_clone)
					lexer_clone = lexer_clone->next;
			}
			var = NULL;
			if (lexer_clone->type == WORD)
				ft_real_expanding(data, lexer_clone, var, new_var);
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
	}
}
