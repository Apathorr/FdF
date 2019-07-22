/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:20:02 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/17 13:12:26 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		hook_key(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 53)
		exit(0);
	if (key == 69)
	{
		mlx->cam->scale += 4.2f;
		mlx_clear_window(mlx, mlx->window);
		render(mlx);
	}
	else if (key == 78)
	{
		mlx->cam->scale -= 4.2f;
		if (mlx->cam->scale < 1)
			mlx->cam->scale = 1;
		mlx_clear_window(mlx, mlx->window);
		render(mlx);
	}
	else if (key == 8)
		change_colour(mlx);
	mlx->button = key;
	return (0);
}

int		key_release(int key, t_mlx *mlx)
{
	(void)mlx;
	(void)key;
	mlx->button = 0;
	return (0);
}

int		hook_mouse_down(int button, int x, int y, t_mlx *mlx)
{
	(void)button;
	(void)x;
	if (y < 0)
		return (0);
	mlx->mouse->isclick = 1;
	return (0);
}

int		hook_mouse_up(int button, int x, int y, t_mlx *mlx)
{
	(void)button;
	(void)x;
	(void)y;
	mlx->mouse->isclick = 0;
	return (0);
}

int		hook_mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (mlx->mouse->isclick && !mlx->button)
	{
		mlx->cam->x += (mlx->mouse->lasty - y) / 420.0f;
		mlx->cam->y -= (mlx->mouse->lastx - x) / 420.0f;
	}
	else if (mlx->mouse->isclick && mlx->button == 256)
	{
		mlx->cam->offsetx += (x - mlx->mouse->lastx);
		mlx->cam->offsety += (y - mlx->mouse->lasty);
	}
	if (mlx->mouse->isclick)
	{
		mlx_clear_window(mlx, mlx->window);
		render(mlx);
	}
	return (0);
}
