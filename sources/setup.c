/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 21:40:01 by seblin            #+#    #+#             */
/*   Updated: 2024/01/15 10:46:14 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "setup.h"

int	fill_split(char **split_line, t_point ***pt_arr, int row)
{
	int	col;

	col = 0;
	while (*split_line && **split_line != '\n')
	{
		**pt_arr = (t_point *) ft_calloc(1, sizeof(t_point));
		if (!**pt_arr)
			return (1);
		(**pt_arr)->init_vect[0] = col++;
		(**pt_arr)->init_vect[1] = row;
		(**pt_arr)->init_vect[2] = ft_atoi(*split_line++);
		(*(*pt_arr)++)->init_vect[MTX - 1] = 1;
	}
	return (0);
}

int	fill_pt_arr(int fd, t_point **pt_arr, int row)
{
	char	*line;
	char	**split_line;
	int		fill_split_stat;

	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		if (!split_line)
			return (free(line), get_next_line(42), 1);
		fill_split_stat = fill_split(split_line, &pt_arr, row++);
		free(line);
		free_ptr_arr((void **) split_line);
		if (fill_split_stat)
			return (get_next_line(42), 1);
		line = get_next_line(fd);
	}
	return (0);
}

t_point	**create_pt_arr(int fd)
{
	t_point	**pt_arr;
	int		pt_arr_len;
	char	*line;

	pt_arr_len = 0;
	line = get_next_line(fd);
	while (line)
	{
		pt_arr_len += ft_wc(line);
		free(line);
		line = get_next_line(fd);
	}
	if (!pt_arr_len)
	{
		ft_printf("no data found.\n");
		return (NULL);
	}
	pt_arr = (t_point **) ft_calloc(pt_arr_len + 1, sizeof(t_point *));
	if (!pt_arr)
		return (NULL);
	return (pt_arr);
}

int	open_file(char *argv[])
{
	int	fd;

	fd = open(*(argv + 1), O_RDONLY);
	if (fd < 0)
		return (perror(*(argv + 1)), 0);
	return (fd);
}

t_point	**input_handle(char *argv[])
{
	t_point	**pt_arr;
	int		fill_stat;
	int		fd;

	fd = open_file(argv);
	if (!fd)
		exit(1);
	pt_arr = create_pt_arr(fd);
	close(fd);
	if (!pt_arr)
		exit(1);
	fd = open_file(argv);
	if (!fd)
		return (free(pt_arr), exit(1), NULL);
	fill_stat = fill_pt_arr(fd, pt_arr, 0);
	close(fd);
	if (fill_stat)
		return (free_ptr_arr((void **) pt_arr), exit(1), NULL);
	return (pt_arr);
}
