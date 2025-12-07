/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:59:01 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 18:50:47 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_separator(char c, char sep)
{
	return (c == sep);
}

int	count_words(const char *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (!is_separator(str[i], sep))
		{
			words++;
			while (str[i] && !is_separator(str[i], sep))
				i++;
		}
		else
			i++;
	}
	return (words);
}

char	*word_splitter(char *str, char sep)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !is_separator(str[i], sep))
		i++;
	word = (char *) malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && !is_separator(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	j = 0;
	words = (char **) malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	while (s[i])
	{
		if (!is_separator(s[i], c))
		{
			words[j++] = word_splitter((char *)&s[i], c);
			while (s[i] && !is_separator(s[i], c))
				i++;
		}
		else
			i++;
	}
	words[j] = 0;
	return (words);
}
/*
int main(void)
{
	char *str = "Ceci est un test !";
	char sep = ' ';
	char **result = ft_split(str, sep);
	int i = 0;

	printf("Résultat de ft_split(\"%s\", '%c'):\n", str, sep);
	while (result[i])
	{
		printf("Mot %d : %s\n", i, result[i]);
		free(result[i]); // Libère chaque mot
		i++;
	}
	free(result); // Libère le tableau de pointeurs

	return 0;
}
*/
