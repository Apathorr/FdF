/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:25:53 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/03 18:33:19 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH	1000
# define WIN_HEIGHT	1000
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

typedef struct	s_cam
{
	int		offsetx;
	int		offsety;
	double	x;
	double	y;
	double	scale;
	int		**matrix;
}			t_cam;

typedef struct	s_mouse
{
	int		isclick;
	int		lastx;
	int		lasty;
	int		x;
	int		y;
}			t_mouse;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
	int		colour;
}			t_point;

typedef struct	s_map
{
	int		width;
	int		height;
	int		depth_min;
	int		depth_max;
	t_point	**points;
}			t_map;

typedef struct 	s_image
{
	void	*image;
	char	*ptr;
	int		bpp;
	int		stride;
	int		endian;
}			t_image;

typedef struct 	s_mlx
{
	void	*mlx;
	void	*window;
	t_image	*image;
	t_map	*map;
	t_cam	*cam;
	t_mouse	*mouse;
	int		button;
}			t_mlx;

typedef struct	s_line
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	int		err;
	int		err2;
	t_point start;
	t_point end;
}			t_line;

/* draw */
void	change_colour(t_mlx *mlx);
void	plotline(t_mlx *mlx, t_point p1, t_point p2);
t_point	rotate(t_point p, t_cam *r);
void	print_help(t_mlx *mlx);
void	render(t_mlx *mlx);

/* map */
t_point	project_point(t_point p, t_mlx *mlx);
t_point	find_point(t_map *map, int x, int y);
t_point	*get_point(int x, int y, char *str);
t_map	*get_map(int width, int height);

/* reader */
/* static int	cleanup(t_list **list, t_map **map); */
/* static int	get_lines(int fd, t_list **list); */
void		find_depth(t_map *map);
/* static int	populate_map(t_list *lst, t_map **map); */
int			read_file(int fd, t_map **map);

/* images */
void	im_set(t_image *image, int x, int y, int colour);
void	clear_im(t_image *image);
t_image	*del_im(t_mlx *mlx, t_image *image);
t_image	*new_im(t_mlx *mlx);

/* hooks */
int		hook_key(int key, t_mlx *mlx);
int		key_release(int key, t_mlx *mlx);
int		hook_mouse_down(int button, int x, int y, t_mlx *mlx);
int		hook_mouse_up(int button, int x, int y, t_mlx *mlx);
int		hook_mouse_move(int x, int y, t_mlx *mlx);

/* main */
int		end(char *reason);
t_mlx	*mlxdel(t_mlx *mlx);
t_mlx	*init(char *title, t_map *map);
int		main(int argc, char **argv);
#endif
