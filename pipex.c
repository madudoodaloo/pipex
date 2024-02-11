/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 03:37:38 by msilva-c          #+#    #+#             */
/*   Updated: 2024/02/09 19:01:04 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_1(char **argv, char **envp, t_pipex *pipex)
{
	pipex->command_split = ft_split(argv[2], ' ', pipex);
	if (!pipex->command_split)
	{
		if (!*argv[3])
			exit_and_free(pipex, NULL);
		else
			exit_and_free(pipex, "malloc");
	}
	pipex->command = path_and_check(envp, pipex->command_split[0], pipex);
	if (pipex->command == NULL)
		exit_and_free(pipex, "command not found");
	pipex->dup_fd[0] = dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	pipex->dup_fd[1] = dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	if (pipex->dup_fd[0] == -1 || pipex->dup_fd[1] == -1)
		exit_and_free(pipex, "dup2");
	if (execve(pipex->command, pipex->command_split, envp) == -1)
		exit_and_free(pipex, "execve");
}

void	command_2(char **argv, char **envp, t_pipex *pipex)
{
	pipex->command_split = ft_split(argv[3], ' ', pipex);
	if (!pipex->command_split)
	{
		if (!*argv[3])
			exit_and_free(pipex, NULL);
		else
			exit_and_free(pipex, "malloc");
	}
	pipex->command = path_and_check(envp, pipex->command_split[0], pipex);
	if (pipex->command == NULL)
		exit_and_free(pipex, "command not found");
	pipex->dup_fd[0] = dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	pipex->dup_fd[1] = dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close(pipex->pipe_fd[1]);
	if (pipex->dup_fd[0] == -1 || pipex->dup_fd[1] == -1)
		exit_and_free(pipex, "dup2");
	if (execve(pipex->command, pipex->command_split, envp) == -1)
		exit_and_free(pipex, "execve");
}

void	ft_second_child(char **argv, char **envp, t_pipex *pipex)
{
	int	child2_pid;

	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	child2_pid = fork();
	if (child2_pid == -1)
		exit_and_free(pipex, "fork");
	else if (child2_pid == 0)
		command_2(argv, envp, pipex);
}

void	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	int	child1_pid;

	if (pipe(pipex->pipe_fd) == -1)
		exit_and_free(pipex, "pipe");
	child1_pid = fork();
	if (child1_pid == -1)
		exit_and_free(pipex, "fork");
	else if (child1_pid == 0)
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			exit_and_free(pipex, "open");
		command_1(argv, envp, pipex);
	}
	ft_second_child(argv, envp, pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		pipex;

	init_all(&pipex);
	if (argc == 5)
	{
		ft_pipex(argv, envp, &pipex);
		exit_and_free(&pipex, NULL);
	}
	else
		exit_and_free(&pipex, NULL);
}
