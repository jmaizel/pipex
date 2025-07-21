/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacobmaizel <jacobmaizel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:36:49 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/01/09 13:46:48 by jacobmaizel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_fds(t_pipex *pipex)
{
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		handle_error(pipex, "dup2 infile failed", NULL);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		handle_error(pipex, "dup2 pipe write failed", NULL);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

static void	parse_and_execute(t_pipex *pipex, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(pipex->cmd1, ' ');
	if (!args)
		handle_error(pipex, "ft_split failed for cmd1", NULL);
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		handle_error(pipex, NULL, args);
	}
	execve(cmd_path, args, envp);
	perror("execve failed for cmd1");
	free(cmd_path);
	free_args(args);
	exit(EXIT_FAILURE);
}

void	execute_cmd1(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		handle_error(pipex, "Fork failed for cmd1", NULL);
	if (pipex->pid1 == 0)
	{
		redirect_fds(pipex);
		parse_and_execute(pipex, envp);
	}
}
