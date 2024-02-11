/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 03:37:59 by msilva-c          #+#    #+#             */
/*   Updated: 2024/02/10 18:58:21 by msilva-c         ###   ########.fr       */
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
	char	**command_split; 
	char	*command;
	int		exit_status;
}			t_pipex;

/* main functions */
void		init_all(t_pipex *pipex);
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
void		ft_free_all(char **path);
int			exit_and_free(t_pipex *pipex, char *msg);

/* split */
char		*word_dup(char *str, int start, int finish);
int			count_words(char *str, char c, t_pipex *pipex);
char		**ft_split2(char *s, char c, char **split);
char		**ft_split(char *str, char ch, t_pipex *pipex);

#endif