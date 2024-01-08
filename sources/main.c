/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/08 20:38:43 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include "mlx.h"

#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "setup.h"
#include <unistd.h>

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

int	fill_split(char **split_line, t_point ***pt_arr, int row)
{
	int		col;
	
	col = 0;
	while (*split_line && **split_line != '\n')
	{
		**pt_arr = (t_point *) ft_calloc(1, sizeof(t_point));
		if (!**pt_arr)			
			return (1);		
		(**pt_arr)->x = col++;
		(**pt_arr)->y = row;
		(*(*pt_arr)++)->z = ft_atoi(*split_line++);				
	}
	return (0);
}

int	fill_pt_arr(int fd, t_point **pt_arr, int row)
{	
	char	*line;
	char	**split_line;
	int 	fill_split_stat;

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

int	open_file(char *argv[])
{
	int	fd;
	
	fd = open(*(argv + 1), O_RDONLY);
	if (fd < 0)
		return (perror(*(argv + 1)), 0);	
	return (fd);
}

void	print_pt_arr(t_point *pt_arr[])
{
	while (*pt_arr)
	{
		ft_printf("x: %d, y: %d, z:%d, nx: %d, ny: %d\n", (*pt_arr)->x, (*pt_arr)->y, (*pt_arr)->z, (*pt_arr)->new_x, (*pt_arr)->new_y);	
		pt_arr++;
	}
}

t_point	**input_handle(char *argv[])
{
	t_point	**pt_arr;
	int 	fill_stat;
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

int	main(int argc, char *argv[])
{
	void	*mlx_connect;
	void	*mlx_window;
	t_point	**pt_arr;
	
	if (argc != 2)
		return (1);	
	pt_arr = input_handle(argv);  
	mlx_connect = mlx_init();
	if (!mlx_connect)
		return (free_ptr_arr((void **) pt_arr), 1); 
	mlx_window = mlx_new_window(mlx_connect, 500, 500, "fdf");
	if (!mlx_window)
		return (free_ptr_arr((void **) pt_arr),
			mlx_destroy_display(mlx_connect), free(mlx_connect), 1);		
	//int		mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
	print_pt_arr(pt_arr);
	// mlx_loop(mlx_connect);	
		
	// mlx_destroy_window(mlx_connect, mlx_window);
	// mlx_destroy_display(mlx_connect);
	// free(mlx_connect);	
	return (0);
}
