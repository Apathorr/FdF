/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:12:44 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/03 18:07:01 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_colour(t_mlx *mlx)
{
	int colour;
	int i;

	i = 0;
	while (mlx->map->points[i])
	{
		colour = mlx->map->points[i]->colour;
		if (colour + 0x0F0000 > 0xFFFFFF)
			colour = 0x2F2F2F - (0xFFFFFF - colour);
		else
			colour += 0xA00000;
		mlx->map->points[i]->colour = colour;
		i++;
	}
	mlx_clear_window(mlx, mlx->window);
	render(mlx);
}

void	plotline(t_mlx *mlx, t_point p1, t_point p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.end = p2;
	line.dx = (int)ft_abs((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ft_abs((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
	{
		im_set(mlx->image, p1.x, p1.y, p1.colour);
		line.err2 = line.err;
		line.err2 > -line.dx ? line.err -= line.dy : 1 == 1;
		line.err2 > -line.dx ? p1.x += line.sx : 1 == 1;
		line.err2 < line.dy ? line.err += line.dx : 1 == 1;
		line.err2 < line.dy ? p1.y += line.sy : 1 == 1;
	}
}

t_point	rotate(t_point p, t_cam *r)
{
	t_point		tmp;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	tmp.x = (cos(r->y) * x + sin(r->y) * z);
	tmp.z = (-sin(r->y) * x + cos(r->y) * z);
	y = p.y;
	z = tmp.z;
	tmp.y = (cos(r->x) * y - sin(r->x) * z);
	tmp.z = (sin(r->x) * y + cos(r->x) * z);
	tmp.colour = p.colour;
	return (tmp);
}

void	print_help(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->window, 42, 42, 0xFFFFFF, "Controls");
	mlx_string_put(mlx->mlx, mlx->window, 42, 72, 0xFFFFFF,
	"Rotate: Click and Drag");
	mlx_string_put(mlx->mlx, mlx->window, 42, 102, 0xFFFFFF,
	"Move: Click and Drag While Holding CTRL");
	mlx_string_put(mlx->mlx, mlx->window, 42, 132, 0xFFFFFF,
	"Change Colour: Space");
	mlx_string_put(mlx->mlx, mlx->window, 42, 162, 0xFFFFFF, "Zoom: +/-");
	mlx_string_put(mlx->mlx, mlx->window, 42, 192, 0xFFFFFF, "Quit: ESC");
}

void	render(t_mlx *mlx)
{
	int		x;
	int		y;
	t_point	tmp;

	clear_im(mlx->image);
	x = 0;
	while (x < mlx->map->width)
	{
		y = 0;
		while (y < mlx->map->height)
		{
			tmp = project_point(find_point(mlx->map, x, y), mlx);
			if (x + 1 < mlx->map->width)
				plotline(mlx, tmp, project_point(find_point(mlx->map, x + 1, y),
				mlx));
			if (y + 1 < mlx->map->height)
				plotline(mlx, tmp, project_point(find_point(mlx->map, x, y + 1),
				mlx));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	print_help(mlx);
}
