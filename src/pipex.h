/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:26:06 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/03/10 16:28:36 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

void	execute(const char *cmd, char *envp[]);
void	pipex(char *cmd, char *envp[]);
void	execute(const char *cmd, char *envp[]);
void	open_here_doc(char	*delimiter);
void	open_fd_files(int	*fd_infile, int	*fd_outfile, char *argv[], int argc);
void	free_split(char	**vector);
void	check_access(int argc, char *argv[]);


#endif