/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agertha <agertha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:45:02 by agertha           #+#    #+#             */
/*   Updated: 2021/10/21 17:28:19 by agertha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *arr, int ch, size_t size)
{
	unsigned int	i;
	char			*result;

	i = 0;
	result = (char *)arr;
	while (i < size)
	{
		result[i] = ch;
		i++;
	}
	return (result);
}
