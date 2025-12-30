/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:52:46 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:53:31 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(int value)
{
	if (value > 47 && value < 58)
		return (value > 0);
	return (0);
}

/*
int main()
{
    char c;
    c='0';
    printf("Result when numeric character is passed: %d", isdigit(c));

    c='+';
    printf("\nResult when non-numeric character is passed: %d", isdigit(c));

    return 0;
}
*/
