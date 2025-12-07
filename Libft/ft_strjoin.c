/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:30:04 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/15 13:47:27 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
	{
		return (ft_strdup(s2));
	}
	if (!s2)
	{
		return (ft_strdup(s1));
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	return (join);
}

/*
int main(void)
{
    char *str1 = "Hello, ";
    char *str2 = "world!";
    char *result;

    result = ft_strjoin(str1, str2);
    if (result)
    {
        printf("Résultat : %s\n", result);
        free(result); // Libérer la mémoire allouée
    }
    else
    {
        printf("Erreur d'allocation ou chaînes NULL.\n");
    }

    return 0;
}
*/
