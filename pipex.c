/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 03:37:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/01/15 18:37:47 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_1(char **argv, char **envp, t_pipex *pipex)
{
	char	*full_path;
	char	**command_split;

	command_split = ft_split(argv[2], ' ', pipex);
	if (!command_split)
		exit_and_free(pipex);
	full_path = path_and_check(envp, command_split[0], pipex);
	if (full_path == NULL)
		exit_and_free(pipex);
	pipex->dup_fd[0] = dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	pipex->dup_fd[1] = dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execve(full_path, command_split, envp);
	/*close(pipex->infile);
	close(pipex->outfile);*/
	exit_and_free(pipex);
}

void	command_2(char **argv, char **envp, t_pipex *pipex)
{
	char	*full_path;
	char	**command_split;

	command_split = ft_split(argv[3], ' ', pipex);
	if (!command_split)
		exit_and_free(pipex);
	full_path = path_and_check(envp, command_split[0], pipex);
	if (full_path == NULL)
	{	
		close(pipex->infile);
		close(pipex->outfile);
		exit_and_free(pipex);
	}
	pipex->dup_fd[0] = dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	pipex->dup_fd[1] = dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close(pipex->pipe_fd[1]);
	execve(full_path, command_split, envp);
/* 	close(pipex->infile);
	close(pipex->outfile); */
/* 	ft_free_all(command_split); */
	exit_and_free(pipex);
}

void	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	int	child1_pid;

	if (pipe(pipex->pipe_fd) == -1)
		exit_and_free(pipex);
	child1_pid = fork();
	if (child1_pid == -1)
		exit_and_free(pipex);
	else if (child1_pid == 0)
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			exit_and_free(pipex);
		close(pipex->pipe_fd[0]);
		command_1(argv, envp, pipex);
	}
	ft_second_child(argv, envp, pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

void	ft_second_child(char **argv, char **envp, t_pipex *pipex)
{
	int	child2_pid;

	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	child2_pid = fork();
	if (child2_pid == -1)
		exit_and_free(pipex);
	else if (child2_pid == 0)
	{
		close(pipex->pipe_fd[1]);
		command_2(argv, envp, pipex);
	}
}

void init_all(t_pipex *pipex)
{
	pipex->exit_status = 1;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->dup_fd[0] = -1;
	pipex->dup_fd[1] = -1;
	pipex->paths = NULL;
	pipex->command = NULL;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		pipex;

	init_all(&pipex);
	if (argc == 5)
	{		
		ft_pipex(argv, envp, &pipex);
		exit_and_free(&pipex);
	}
	else
		exit_and_free(&pipex);
}
