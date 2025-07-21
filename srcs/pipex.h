/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacobmaizel <jacobmaizel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:55:48 by jacobmaizel       #+#    #+#             */
/*   Updated: 2025/01/09 13:30:53 by jacobmaizel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
}			t_pipex;

void		free_args(char **args);
int			contains_char(const char *s, char c);

char		*find_path(char *cmd, char **envp);
void		free_args(char **args);
void		handle_error(t_pipex *pipex, const char *msg, char **args);
void		check_arguments(int argc, char **argv);
int			open_infile(char *infile);
int			open_outfile(char *outfile);
void		create_pipe(t_pipex *pipex);
void		execute_cmd1(t_pipex *pipex, char **envp);
void		execute_cmd2(t_pipex *pipex, char **envp);
#endif