/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:10:17 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/02/09 17:26:03 by msilva-c         ###   ########.fr       */
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
	str = NULL;
	if (access(command, F_OK) == 0)
		return (ft_strjoin(command, ""));
	while (pipex->paths[i])
	{
		str = ft_strjoin(pipex->paths[i], command);
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		i++;
	}
	if (pipex->paths[i] == NULL)
		return (ft_strjoin(command, ""));
	return (str);
}

char	*path_and_check(char **envp, char *command, t_pipex *pipex)
{
	int		i;
	char	*temp1;

	i = 0;
	if (!command)
		exit_and_free(pipex, "malloc");
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	pipex->paths = ft_split(envp[i] + 5, ':', pipex);
	if (!pipex->paths)
		exit_and_free(pipex, "malloc");
	i = -1;
	while (pipex->paths[++i])
	{
		temp1 = ft_strjoin(pipex->paths[i], "/");
		free(pipex->paths[i]);
		pipex->paths[i] = temp1;
	}
	return (path_and_check2(command, pipex));
}
