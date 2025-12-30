/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:05:07 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:05:56 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < len && to_find[j])
			j++;
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

/*
int main() {
    const char *haystack = "Bonjour tout le monde";
    const char *needle = "tout";
    size_t len = 5;

    char *result = strnstr(haystack, needle, len);

    if (result != NULL) {
        printf("Sous-chaîne trouvée : \"%s\"\n", result);
    } else {
        printf("Sous-chaîne non trouvée.\n");
    }

    return 0;
}
*/
