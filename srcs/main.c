/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:37 by jmaizel           #+#    #+#             */
/*   Updated: 2024/12/24 15:25:41 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Fonction pour vérifier les arguments
** Vérifie que le nombre d'arguments est correct
*/
void	check_arguments(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

/*
** Fonction pour ouvrir le fichier d'entrée
** Ouvre le fichier d'entrée en lecture et retourne le descripteur
*/
int	open_infile(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	return (infile_fd);
}

/*
** Fonction pour ouvrir le fichier de sortie
** Ouvre le fichier de sortie en écriture,
	le crée s'il n'existe pas et retourne le descripteur
*/
int	open_outfile(char *outfile)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("Error opening outfile");
		exit(EXIT_FAILURE);
	}
	return (outfile_fd);
}

/*
** Fonction pour créer le pipe
** Crée un pipe et stocke les descripteurs dans pipex->pipe_fd
*/
void	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		handle_error(pipex, "Pipe creation failed", NULL);
	}
}

/*
** Fonction pour exécuter la première commande
** Crée un processus enfant, redirige les entrées/sorties et exécute cmd1
*/
void	execute_cmd1(t_pipex *pipex, char *cmd1, char **envp)
{
	char	**args;
	char	*cmd_path;

	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		handle_error(pipex, "Fork failed for cmd1", NULL);
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			handle_error(pipex, "dup2 infile failed", NULL);
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			handle_error(pipex, "dup2 pipe write failed", NULL);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		args = ft_split(cmd1, ' ');
		if (!args)
			handle_error(pipex, "ft_split failed for cmd1", NULL);
		cmd_path = find_path(args[0], envp);
		if (!cmd_path)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			free_args(args);
			handle_error(pipex, NULL, args);
		}
		execve(cmd_path, args, envp);
		perror("execve failed for cmd1");
		free(cmd_path);
		free_args(args);
		exit(EXIT_FAILURE);
	}
}

/*
** Fonction pour exécuter la deuxième commande
** Crée un processus enfant, redirige les entrées/sorties et exécute cmd2
*/
void	execute_cmd2(t_pipex *pipex, char *cmd2, char **envp)
{
	char	**args;
	char	*cmd_path;

	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		handle_error(pipex, "Fork failed for cmd2", NULL);
	if (pipex->pid2 == 0)
	{
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
			handle_error(pipex, "dup2 pipe read failed", NULL);
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
			handle_error(pipex, "dup2 outfile failed", NULL);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		args = ft_split(cmd2, ' ');
		if (!args)
			handle_error(pipex, "ft_split failed for cmd2", NULL);
		cmd_path = find_path(args[0], envp);
		if (!cmd_path)
			fprintf(stderr, "Command not found: %s\n", args[0]);
		free_args(args);
		handle_error(pipex, NULL, args);
		execve(cmd_path, args, envp);
		perror("execve failed for cmd2");
		free(cmd_path);
		free_args(args);
		exit(EXIT_FAILURE);
	}
}

/*
** Fonction principale
** Gère la création des processus, les redirections et l'exécution des commandes
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;

	pipex.infile_fd = -1;
	pipex.outfile_fd = -1;
	pipex.pipe_fd[0] = -1;
	pipex.pipe_fd[1] = -1;
	check_arguments(argc, argv);
	infile = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	outfile = argv[4];
	pipex.infile_fd = open_infile(infile);
	pipex.outfile_fd = open_outfile(outfile);
	create_pipe(&pipex);
	execute_cmd1(&pipex, cmd1, envp);
	execute_cmd2(&pipex, cmd2, envp);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (EXIT_SUCCESS);
}
