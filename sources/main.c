/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:23:25 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/17 13:17:27 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		end(char *reason)
{
	ft_putendl(reason);
	return (1);
}

t_mlx	*mlxdel(t_mlx *mlx)
{
	if (mlx->window)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->cam)
		ft_memdel((void**)&mlx->cam);
	if (mlx->mouse)
		ft_memdel((void**)&mlx->mouse);
	if (mlx->image)
		del_im(mlx, mlx->image);
	if (mlx->map)
		ft_memdel((void**)&mlx->map);
	return (NULL);
}

t_mlx	*init(char *title, t_map *map)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) == NULL ||
		(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL ||
		(mlx->image = new_im(mlx)) == NULL ||
		(mlx->cam = ft_memalloc(sizeof(t_cam))) == NULL)
		return (mlxdel(mlx));
	free(title);
	mlx->map = map;
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
	mlx->button = 0;
	return (mlx);
}

int		main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		return (end("usage: fdf< file>"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || !read_file(fd, &map))
		return (end("error: invlaid file"));
	if (!(mlx = init(ft_strjoin("Fdf - ", argv[1]), map)))
		return (end("error: mlx couldn't initialize"));
	render(mlx);
	mlx_hook(mlx->window, 4, 0, hook_mouse_down, mlx);
	mlx_hook(mlx->window, 5, 0, hook_mouse_up, mlx);
	mlx_hook(mlx->window, 6, 0, hook_mouse_move, mlx);
	mlx_hook(mlx->window, 3, 0, key_release, mlx);
	mlx_hook(mlx->window, 2, 0, hook_key, mlx);
	mlx_loop(mlx);
	return (0);
}
