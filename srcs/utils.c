/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:07:43 by jmaizel           #+#    #+#             */
/*   Updated: 2025/01/10 12:55:24 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Fonction pour gérer les erreurs
** Affiche un message d'erreur, ferme les descripteurs et libère les ressources
*/
void	handle_error(t_pipex *pipex, const char *msg, char **args)
{
	if (msg)
		perror(msg);
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
	if (pipex->pipe_fd[0] >= 0)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] >= 0)
		close(pipex->pipe_fd[1]);
	if (args)
		free_args(args);
	exit(EXIT_FAILURE);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	contains_char(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// Fonction pour ouvrir le fichier d'entrée
// Ouvre le fichier d'entrée en lecture et retourne le descripteur

int	open_infile(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("Error opening infile");
	}
	return (infile_fd);
}

// Fonction pour ouvrir le fichier de sortie
// Ouvre le fichier de sortie en écriture,
// le crée s'il n'existe pas et retourne le descripteur

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
