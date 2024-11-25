/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:13:24 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/03/10 16:27:13 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = envp[i] + 5;
			break;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	return(ft_split(path, ':'));
}

static void	process(int	fd_close, int fd_dup, char *cmd, char *envp[])
{
	close(fd_close);
	dup2(fd_dup, STDOUT_FILENO);
	close(fd_dup);
	execute(cmd, envp);
}

static void	exec_path(char **my_paths, char	**cmd_args, char *envp[])
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	while (my_paths[i])
	{
        tmp = ft_strjoin(my_paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
	perror("Command not not found");
}

void	execute(const char *cmd, char *envp[])
{
	char	**cmd_args;
	char	**my_paths;

	my_paths = ft_path(envp);
	cmd_args = ft_split(cmd, ' ');
	exec_path(my_paths, cmd_args, envp);
	free_split(my_paths);
	free_split(cmd_args);
	exit(EXIT_FAILURE);
	return ;
}

void	pipex(char *cmd, char *envp[])
{
	int		fd_pipe[2];
	pid_t	child_pid;

	if (pipe(fd_pipe) == -1)
	{
		perror("Error creating the pipe");
		exit(EXIT_FAILURE);
	}
	if ((child_pid = fork()) == -1)
	{
		perror("Error creating the child process");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
		process(fd_pipe[0], fd_pipe[1], cmd, envp);
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		waitpid(child_pid, NULL, 0);
	}
}
