/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:06:08 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:07:10 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int value)
{
	if ((value > 64 && value < 91) || (value > 96 && value < 123)
		|| (value > 47 && value < 58))
		return (1);
	return (0);
}
/*
#include <stdio.h>
void main(void)
{
    char *t = " ";
    int i = 0;
    printf("%d", isalnum(*t));
}
*/
