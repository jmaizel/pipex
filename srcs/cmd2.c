/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacobmaizel <jacobmaizel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:38:26 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/01/09 13:46:52 by jacobmaizel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_fds_cmd2(t_pipex *pipex)
{
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		handle_error(pipex, "dup2 pipe read failed", NULL);
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		handle_error(pipex, "dup2 outfile failed", NULL);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

static void	parse_and_execute_cmd2(t_pipex *pipex, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(pipex->cmd2, ' ');
	if (!args)
		handle_error(pipex, "ft_split failed for cmd2", NULL);
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		handle_error(pipex, NULL, args);
	}
	execve(cmd_path, args, envp);
	perror("execve failed for cmd2");
	free(cmd_path);
	free_args(args);
	exit(EXIT_FAILURE);
}

void	execute_cmd2(t_pipex *pipex, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		handle_error(pipex, "Fork failed for cmd2", NULL);
	if (pipex->pid2 == 0)
	{
		redirect_fds_cmd2(pipex);
		parse_and_execute_cmd2(pipex, envp);
	}
}
