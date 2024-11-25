/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:29:08 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/03/10 16:24:47 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_error(int argc,char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5)
	{
		perror("Usage: ./pipex infile [cmd1] [cmd2] ... outfile");
		exit(EXIT_FAILURE);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			perror("Empty argument detected");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	check_access(argc, argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_infile;
	int		fd_outfile;
	int	i;

	fd_infile = 0;
	fd_outfile = 0;
	check_error(argc, argv);
	open_fd_files(&fd_infile, &fd_outfile, argv, argc);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		i = 3;
		open_here_doc(argv[2]);
	}
	else
	{
		i = 2;
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	while (i < argc - 2)
		pipex(argv[i++], envp);
	dup2(fd_outfile, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
	close(fd_outfile);
	return (0);
}
