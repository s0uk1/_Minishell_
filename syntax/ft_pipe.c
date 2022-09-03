/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:23 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/03 11:51:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skip_norme(t_lexer *lexer_clone, int num)
{
	lexer_clone = lexer_clone->next;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		num++;
		lexer_clone = lexer_clone->next;
	}
	return (num);
}

int	ft_idk(t_data *data, t_lexer *lexer_clone, int num)
{
	if (lexer_clone && lexer_clone->type == PIPE && num == 0)
	{
		printf("Syntax error near unexpected token `|'\n");
		data->exit_stat = 258;
	}
	return (0);
}

int	ft_check_between_pipes(t_data *data)
{
	t_lexer	*lexer_clone;
	int		num;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		num = 0;
		if (lexer_clone->type == PIPE)
		{
			lexer_clone = lexer_clone->next;
			while (lexer_clone && lexer_clone->type != PIPE)
			{
				num++;
				lexer_clone = lexer_clone->next;
			}
			if (!lexer_clone)
				break ;
			if (ft_idk(data, lexer_clone, num))
				break ;
		}
		if (lexer_clone->type != PIPE)
			lexer_clone = lexer_clone->next;
	}
	return (data->exit_stat);
}
