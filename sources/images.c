/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 10:38:08 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/03 18:07:50 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	im_set(t_image *image, int x, int y, int colour)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int*)(image->ptr + ((x + y * WIN_WIDTH) * image ->bpp)) = colour;
}

void	clear_im(t_image *image)
{
	ft_bzero(image->ptr, WIN_WIDTH * WIN_HEIGHT * image->bpp);
}

t_image *del_im(t_mlx *mlx, t_image *image)
{
	if (image != NULL)
	{
		if (image->image)
			mlx_destroy_image(mlx->mlx, image->image);
		ft_memdel((void**)&image);
	}
	return (NULL);
}
t_image *new_im(t_mlx *mlx)
{
	t_image *image;

	if (!(image = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(image->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT)))
		return(del_im(mlx, image));
	image->ptr = mlx_get_data_addr(image->image, &image->bpp, &image->stride,
	 	&image->endian);
	image->bpp /= 8;
	return (image);
}
