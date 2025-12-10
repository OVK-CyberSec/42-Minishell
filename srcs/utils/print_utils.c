/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnakasto <mnakasto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:56:12 by mnakasto          #+#    #+#             */
/*   Updated: 2025/12/10 21:59:20 by mnakasto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_one_redir(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		printf(" < %s\n", redir->file);
	else if (redir->type == REDIR_OUT)
		printf(" > %s\n", redir->file);
	else if (redir->type == REDIR_APPEND)
		printf(" >> %s\n", redir->file);
	else if (redir->type == REDIR_HEREDOC)
		printf(" << %s\n", redir->file);
}

void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
	{
		printf("Arguments: none\n");
		return ;
	}
	printf("Arguments:\n");
	while (cmd->args[i])
	{
		printf("  [%d] = \"%s\"\n", i, cmd->args[i]);
		i++;
	}
}

void	print_cmd_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd->redirs)
	{
		printf("Redirections: none\n");
		return ;
	}
	printf("Redirections:\n");
	redir = cmd->redirs;
	while (redir)
	{
		print_one_redir(redir);
		redir = redir->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	int	cmd_num;

	cmd_num = 0;
	while (cmds)
	{
		printf("\n===Command %d ===\n", cmd_num);
		print_cmd_args(cmds);
		print_cmd_redirs(cmds);
		cmds = cmds->next;
		cmd_num++;
	}
}
