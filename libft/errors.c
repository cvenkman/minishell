/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:02:31 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:53:35 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
**	@brief	display error and exit
**	
**	@param	str		display error
*/
void	putstr_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/**
**	@brief	executes the perror and exit with errno
**	
**	@param	str		display error
*/
void	perror_exit(char *str)
{
	if (str)
		perror(str);
	else
		perror(NULL);
	exit(errno);
}

/**
**	@brief	executes the perror
**	
**	@param	str		display error
**	@return	void
*/
void	perror_return(char *str)
{
	if (str)
		perror(str);
	else
		perror(NULL);
}

/**
**	@brief	executes the perror
**	
**	@param	str		display error
**	@return	int		num
*/
int	perror_return_number(char *str, int num)
{
	if (str)
		perror(str);
	else
		perror(NULL);
	return (num);
}

/**
**	@brief	display error and return -1
**	
**	@param	str		display error
**	@return	int	-1
*/
int	error_return(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}
