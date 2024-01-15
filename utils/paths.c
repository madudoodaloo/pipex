/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:10:17 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/01/15 18:40:03 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_all(char **path)
{
	int		i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
}

char	*path_and_check2(char *command, t_pipex *pipex)
{
	char	*str;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		str = ft_strjoin(pipex->paths[i], command);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		i++;
	}
	if (pipex->paths[i] == NULL)
	{
		//ft_free_all(pipex->paths);
		return (command);
	}
	//ft_free_all(pipex->paths);
	return (str);
}

char	*path_and_check(char **envp, char *command, t_pipex *pipex)
{
	int		i;
	char	*temp1;

	i = 0;
	if (!command)
		exit_and_free(pipex);
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	pipex->paths = ft_split(envp[i] + 5, ':', pipex);
	if (!pipex->paths)
		exit_and_free(pipex);
	i = -1;
	while (pipex->paths[++i])
	{
		temp1 = pipex->paths[i];
		pipex->paths[i] = ft_strjoin(temp1, "/");
		free(temp1);
	}
	return (path_and_check2(command, pipex));
}
