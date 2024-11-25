/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:19:03 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/03/10 16:25:01 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_here_doc(char *delimeter, int fd_write)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
}

void	open_here_doc(char	*delimiter)
{
	int		fd_pipe[2];
	pid_t	child_pid;

	if (pipe(fd_pipe) == -1)
	{
		perror("Error creating the pipe");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error creating child process");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		close(fd_pipe[0]);
		read_here_doc(delimiter, fd_pipe[1]);
	}
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		waitpid(child_pid, NULL, 0);
	}
}

void	open_fd_files(int	*fd_infile, int	*fd_outfile, char *argv[], int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			perror("Usage: ./pipex here_doc [EOF] [cmd1] [cmd2] ... outfile");
			exit(EXIT_FAILURE);
		}
		*fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_outfile == -1)
		{
			perror("Error opening the files");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		*fd_infile = open(argv[1], O_RDONLY);
		*fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR| O_TRUNC, 0777);
		if (*fd_infile == -1 || *fd_outfile == -1)
		{
			perror("Error opening the files");
			exit(EXIT_FAILURE);
		}
	}
}

void	free_split(char	**vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}

void	check_access(int argc, char *argv[])
{
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if (access(argv[argc - 1], W_OK) == -1)
		{
			perror("Error to access \"write\" outfile");
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		if (access(argv[1], R_OK) == -1)
		{
			perror("Error to access \"read\" infile");
			exit(EXIT_FAILURE);
		}
	}
}
