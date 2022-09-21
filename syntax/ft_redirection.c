/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:27 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/15 18:08:28 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_output_err(t_data *data, char *value)
{
	data->exit_stat = 258;
	printf("Syntax error near unexpected token `%s'\n", value);
}

static int	ft_check_red(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone->next)
		lexer_clone = lexer_clone->next;
	if (lexer_clone->type == REDIRECTION)
	{
		data->exit_stat = 258;
		printf("Syntax error near unexpected token `newline'\n");
		return (data->exit_stat);
	}
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strlen(lexer_clone->val) > 2)
		{
			ft_output_err(data, lexer_clone->val);
			return (data->exit_stat);
		}
		lexer_clone = lexer_clone->next;
	}
	return (data->exit_stat);
}

static int	ft_check_type(int lexer_clone_type)
{
	if (lexer_clone_type == PIPE || lexer_clone_type == REDIRECTION)
		return (1);
	return (0);
}

static int	ft_check_after_red(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == REDIRECTION)
		{
			lexer_clone = lexer_clone->next;
			while (lexer_clone->next)
			{
				if (ft_check_type(lexer_clone->type))
				{
					ft_output_err(data, lexer_clone->val);
					return (data->exit_stat);
				}
				else
					break ;
				lexer_clone = lexer_clone->next;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (data->exit_stat);
}

int	ft_check_redirection(t_data *data)
{	
	data->exit_stat = ft_check_red(data);
	if (data->exit_stat)
		return (data->exit_stat);
	data->exit_stat = ft_check_after_red(data);
	if (data->exit_stat)
		return (data->exit_stat);
	return (data->exit_stat);
}
