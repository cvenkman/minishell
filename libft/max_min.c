/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:51:42 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:51:42 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

long	min(long a, long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
