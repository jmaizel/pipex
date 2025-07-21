/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacobmaizel <jacobmaizel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:25:11 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/01/09 13:48:33 by jacobmaizel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Fonction pour vérifier les arguments
// Vérifie que le nombre d'arguments est correct

void	check_arguments(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

// Fonction pour créer le pipe
// Crée un pipe et stocke les descripteurs dans pipex->pipe_fd

void	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		handle_error(pipex, "Pipe creation failed", NULL);
	}
}
