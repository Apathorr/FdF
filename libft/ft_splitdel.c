/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:24:15 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/03 18:27:42 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_splitdel(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = *split;
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*split)[i];
	}
	ft_memdel((void**)split);
	return (0);
}
