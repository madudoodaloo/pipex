/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:14:08 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/02/10 18:26:00 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_all(t_pipex *pipex)
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
	pipex->command_split = NULL;
}

int	exit_and_free(t_pipex *pipex, char *msg)
{
	if (msg)
		perror(msg);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->dup_fd[0] != -1)
		close(pipex->dup_fd[0]);
	if (pipex->dup_fd[1] != -1)
		close(pipex->dup_fd[1]);
	if (pipex->command != NULL)
		free(pipex->command);
	if (pipex->paths != NULL)
		ft_free_all(pipex->paths);
	if (pipex->command_split != NULL)
		ft_free_all(pipex->command_split);
	exit(EXIT_FAILURE);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;
	int				diff;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while ((c1[i] != '\0' || c2[i]) != '\0' && i < n)
	{
		if (c1[i] != c2[i])
		{
			diff = c1[i] - c2[i];
			return (diff);
		}
		i++;
	}
	if (i == n)
		return (0);
	return (c1[i] - c2[i]);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	char	*cpy;

	dst = NULL;
	cpy = NULL;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+ 1));
	if (dst && s1 && s2)
	{
		cpy = dst;
		while (*s1 != '\0')
			*dst++ = *s1++;
		while (*s2 != '\0')
			*dst++ = *s2++;
		*dst = '\0';
	}
	else
		return (NULL);
	return (cpy);
}
