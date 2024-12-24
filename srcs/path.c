/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:20:59 by jmaizel           #+#    #+#             */
/*   Updated: 2024/12/24 15:23:28 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Sous-fonction pour libérer un tableau de chaînes alloué par ft_split
static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// Sous-fonction pour construire le chemin complet d'une commande
// Concatène le répertoire avec '/' et la commande
// Retourne le chemin complet ou NULL en cas d'erreur
static char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

// Sous-fonction pour diviser la chaîne PATH en répertoires individuels
// Utilise ft_split pour diviser la chaîne en fonction de ':'
// Retourne un tableau de chaînes ou NULL en cas d'erreur
static char	**split_paths(char *path_env)
{
	char	**paths;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

// Sous-fonction pour extraire la variable PATH des variables d'environnement
// Retourne le pointeur vers la chaîne PATH ou NULL si non trouvé
static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char *path_env;
	char **paths;
	char *full_path;
	int i;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = split_paths(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = build_full_path(paths[i], cmd);
		if (!full_path)
		{
			free_split(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}