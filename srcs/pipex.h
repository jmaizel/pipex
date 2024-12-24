#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>    // Pour errno
# include <fcntl.h>    // Pour les drapeaux O_RDONLY, O_WRONLY, etc.
# include <stdio.h>    // Pour printf, fprintf, perror
# include <stdlib.h>   // Pour exit, malloc, free
# include <string.h>   // Pour strerror
# include <sys/wait.h> // Pour waitpid
# include <unistd.h>   // Pour close, fork, pipe, dup2, execve

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
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
void		execute_cmd1(t_pipex *pipex, char *cmd1, char **envp);
void		execute_cmd2(t_pipex *pipex, char *cmd2, char **envp);
#endif