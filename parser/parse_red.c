/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:12:02 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:15:48 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_file_name(char **cmd, int fname_start, char **dst)
{
	int		j;
	char	*buf;
	int		res;

	buf = ft_strchrs(*cmd + fname_start, " <>");
	if (buf)
		buf = ft_substr(*cmd, fname_start, buf - (*cmd + fname_start));
	else
		buf = ft_substr(*cmd, fname_start, ft_strlen(*cmd + fname_start));
	chmllc(buf);
	j = -1;
	res = ft_strlen(buf);
	while (buf[++j])
	{
		if (buf[j] == '\"' || buf[j] == '\'')
		{
			set_free((void **)&buf, replace_substr(buf, chstr(buf[j]), "", j));
			j = skip_untill_chr(buf + j, chstr(-1)[0]) - buf;
			set_free((void **)&buf, replace_substr(buf, chstr(-1), "", j));
		}
	}
	*dst = buf;
	return (res);
}
