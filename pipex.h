/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 03:37:59 by msilva-c          #+#    #+#             */
/*   Updated: 2024/01/15 18:10:31 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	int		dup_fd[2];
	char	**paths; 
	char	*command;
	int		exit_status;
}			t_pipex;

/* main functions */
void		ft_pipex(char **argv, char **envp, t_pipex *pipex);
void		ft_second_child(char **argv, char **envp, t_pipex *pipex);
void		command_1(char **argv, char **envp, t_pipex *pipex);
void		command_2(char **argv, char **envp, t_pipex *pipex);

/* utils */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);

/* path handle */
char		*path_and_check(char **envp, char *command, t_pipex *pipex);
char		*path_and_check2(char *command, t_pipex *pipex);

/* memory management */
void		error(void);
void		ft_free_all(char **path);
int			exit_and_free(t_pipex *pipex);

/* split */
char		*triple_strjoin(char *s1, char *s2, char *s3);
char		**ft_split(char *str, char ch, t_pipex *pipex);
void		*ft_memcpy(void *dest, const void *src, size_t n);

#endif