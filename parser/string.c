/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:58:34 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:58:34 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchrs(const char *str, const char *chrs)
{
	char	*res;
	char	*tmp;

	if (!str || !chrs)
		return (NULL);
	res = (char *)str + ft_strlen(str);
	while (*(unsigned char *)str)
	{
		tmp = (char *)chrs;
		while (*tmp)
		{
			if (*(unsigned char *) str == *tmp)
				break ;
			tmp++;
		}
		if (*tmp && str < res)
			res = (char *)str;
		str++;
	}
	if (!(*res))
		return (NULL);
	return (res);
}

/**
 * Replace first occurrence substring <b><i>substr</i></b>
 * in string <b><i>str</i></b>
 * @param str string to search substring
 * @param substr string which will be replaced if found
 * @param replacement string to replacement
 * @param pos position in <b><i>str</i></b> from which to search
 * <b><i>substr</i></b>
 * @return new string in which first found <b><i>substr</i></b> will be
 * replaced with <b><i>replacement</i></b> or <b><i>str</i></b> if wasn't found
 */
char	*replace_substr(char *str, char *substr, char *replacement, int pos)
{
	char	*res;
	char	*place;
	int		len;

	place = ft_strstr(str + pos, substr);
	if (place == NULL)
		return (str);
	len = ft_strlen(str) - ft_strlen(substr) + ft_strlen(replacement);
	res = chmllc(ft_calloc(len + 1, sizeof(char)));
	len = place - str;
	ft_strlcpy(res, str, len + 1);
	ft_strcpy(res + len, replacement);
	ft_strcpy(res + len + ft_strlen(replacement), place + ft_strlen(substr));
	return (res);
}

/**
 * Shrink few repeating characters to a single character.
 * Example: "aaaa" -> "a".
 * @param str string to change
 * @param pos position with symbols to replace
 * @param ch symbol to collapse
 * @return string without repeating characters <b><i>ch</i></b>
 * in this position in string or <b><i>str</i></b> if there isn't
 * repeating characters
 */
char	*shrink_chs_one(char *str, int pos, char ch)
{
	int		i;
	char	*to_collapse;
	char	*res;
	char	ch_str[2];

	i = 0;
	ch_str[0] = ch;
	ch_str[1] = '\0';
	while (str[pos + i] == ch)
		i++;
	if (i == 0 || i == 1)
		return (str);
	to_collapse = chmllc(ft_calloc(i + 1, sizeof(char)));
	ft_strlcpy(to_collapse, str + pos, i + 1);
	res = replace_substr(str, to_collapse, ch_str, pos);
	free(to_collapse);
	return (res);
}

char	*skip_untill_chr(char *str, char chr)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != chr)
		i++;
	return (str + i);
}

char	*substr_till_chr(char *str, char chr, int start)
{
	return (ft_substr(str, start,
			skip_untill_chr(str + start, chr) - (str + start)));
}
