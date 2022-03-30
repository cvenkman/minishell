/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:43:30 by cvenkman          #+#    #+#             */
/*   Updated: 2021/09/20 20:11:59 by tphlogis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	u;
	size_t	temp_i;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < n)
	{
		u = 0;
		if (big[i] == little[u])
		{
			temp_i = i;
			while (big[temp_i] == little[u] && temp_i++ < n)
			{
				u++;
				if (little[u] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}
