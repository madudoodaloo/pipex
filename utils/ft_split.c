/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:33:37 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/01/15 18:47:26 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	count_words(char *str, char c, t_pipex *pipex)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	if (str[0] == c)
		exit_and_free(pipex); // mandar pipex para esta função para poder dar close 
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *s, char c, t_pipex *pipex)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !*s)
		return (NULL);
	split = malloc((count_words(s, c, pipex) + 1) * sizeof(char *));
	if (!s || !(split))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
