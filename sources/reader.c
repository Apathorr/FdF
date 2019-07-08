/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:24:25 by rsmith            #+#    #+#             */
/*   Updated: 2019/07/08 12:30:17 by rsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* free up memory if the map cannot be retrieved */

static int		cleanup(t_list **list, t_map **map)
{
		t_list *next;

		while (*list)
		{
			next = (*list) ->next;
			ft_memdel(&(*list)->content);
			ft_memdel((void**)list);
			*list = next;
		}
		if (map && *map)
		{
			ft_memdel((void **)&(*map)->points);
			ft_memdel((void **)map);
		}
		return (0);
}

static int		get_lines(int fd, t_list **list)
{
	t_list	*tmp;
	int		expected;
	char	*line;
	int		ret;

	expected = -1;
	while ((ret = get_next_line(fd, &line)))
	{
		if (expected == -1)
			expected = (int)ft_wordcount(line, ' ');
		tmp = ft_lstnew(line, ft_strlen(line) + 1);
		if (tmp == NULL)
			return(cleanup(list, NULL));
		ft_lstadd(list, tmp);
		if (expected != (int)ft_wordcount(line, ' '))
			return (cleanup(list, NULL));
		ft_strdel(&line);
	}
	if (expected == -1 || ret == -1)
		return (cleanup(list, NULL));
	ft_lstrev(list);
	return (1);
}

void	find_depth(t_map *map)
{
	int		min;
	int		max;
	t_point	tmp1;
	t_point	tmp2;

	min = 2147483647;
	max = -2147483648;
	tmp1.y = 0;
	while (tmp1.y < map->height)
	{
		tmp1.x = 0;
		while (tmp1.x < map->width)
		{
			tmp2 = find_point(map, tmp1.x, tmp1.y);
			if (tmp2.z < min)
				min = tmp2.z;
			if (tmp2.z > max)
				max = tmp2.z;
			tmp1.x++;
		}
		tmp1.y++;
	}
	map->depth_max = max;
	map->depth_min = min;
}

static int	populate_map(t_list *lst, t_map **map)
{
	t_list	*tmp;
	char	**split;
	int		x;
	int		y;

	tmp = lst;
	y = 0;
	while (y < (*map)->height)
	{
		x = 0;
		if (!(split = ft_strsplit(tmp->content, ' ')))
			return (cleanup(&lst, map));
		while (x < (*map)->width)
		{
			(*map)->points[y * (*map)->width + x] = get_point(x, y, split[x]);
			x++;
		}
		ft_splitdel(&split);
		tmp = tmp->next;
		y++;
	}
	find_depth(*map);
	cleanup(&lst, NULL);
	return (1);
}

int			read_file(int fd, t_map **map)
{
	t_list *list;

	list = NULL;
	if (!(get_lines(fd, &list)))
		return (0);
	*map = get_map(ft_wordcount(list->content, ' '), ft_lstcount(list));
	if (map == NULL)
		return (cleanup(&list, map));
	return (populate_map(list, map));
}
