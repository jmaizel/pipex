/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:37 by jmaizel           #+#    #+#             */
/*   Updated: 2025/01/10 12:52:43 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_pipex(t_pipex *pipex)
{
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
	pipex->infile = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->outfile = NULL;
}

void	assign_arguments(t_pipex *pipex, char **argv)
{
	pipex->infile = argv[1];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->outfile = argv[4];
}

void	close_all_fds(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
}

void	wait_for_children(t_pipex *pipex)
{
	if (pipex->pid1 > 0)
		waitpid(pipex->pid1, NULL, 0);
	if (pipex->pid2 > 0)
		waitpid(pipex->pid2, NULL, 0);
}

// Fonction principale
// Gère la création des processus, les redirections et l'exécution des commandes

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	initialize_pipex(&pipex);
	check_arguments(argc, argv);
	assign_arguments(&pipex, argv);
	pipex.infile_fd = open_infile(pipex.infile);
	pipex.outfile_fd = open_outfile(pipex.outfile);
	if (pipex.infile_fd < 0)
	{
		pipex.infile_fd = open("/dev/null", O_RDONLY);
		if (pipex.infile_fd < 0)
			handle_error(&pipex, "Failed to open /dev/null", NULL);
	}
	create_pipe(&pipex);
	execute_cmd1(&pipex, envp);
	execute_cmd2(&pipex, envp);
	close_all_fds(&pipex);
	wait_for_children(&pipex);
	return (EXIT_SUCCESS);
}
