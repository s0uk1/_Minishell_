/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:37:19 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/30 14:24:35 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_initialize2(t_data *data)
{
	g_vars.g_where_ami = 1;
	data->lst_cmd = NULL;
	data->lst_lexer = NULL;
	data->her_doc = 0;
	data->general.index = 0;
	g_vars.g_exit_stat = 0;
}

void	ft_free_norme(t_data *data)
{
	if (data->her_doc)
		free_split(data->eof);
	if (data->paths)
		free_split(data->paths);
	ft_free_lexer(data->lst_lexer);
	ft_free_cmd(data->lst_cmd);
}

void	ft_start(t_data *data)
{
	ft_expanding(data);
	ft_parsing(data);
	pre_execution(data);
	ft_free_norme(data);
}
void	init_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

int	ft_sub_main(t_data *data)
{
	while (42)
	{
		g_vars.g_heredoc = 1;
		init_sig();
		ft_initialize2(data);
		data->cmd = readline("minishell-1.0> ");
		g_vars.g_where_ami = 0;
		if (!data->cmd)
			break ;
		if (data->cmd && data->cmd[0] != '\0')
		{
			ft_lexer(data);
			g_vars.g_exit_stat = ft_syntax_analyzer(data);
			if (g_vars.g_exit_stat == 258)
			{
				ft_free_lexer(data->lst_lexer);
				data->general.old_error = g_vars.g_exit_stat;
				continue ;
			}
			ft_start(data);
		}
		data->general.old_error = g_vars.g_exit_stat;
	}
	rl_clear_history();
	ft_free_env(data, data->lst_env);
	return (0);
}
