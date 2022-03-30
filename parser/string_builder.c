/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:58:37 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:58:37 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*chstr(char c)
{
	static char	chstr[2] = {0, 0};

	if (c >= 0)
		chstr[0] = c;
	return (chstr);
}

char	*ft_strldup(const char *str, int len)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len + 1);
	return (new_str);
}

char	*chrdup(char ch, unsigned int len)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_memset(new_str, ch, len);
	return (new_str);
}
