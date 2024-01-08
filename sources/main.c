/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/08 13:45:14 by svidot           ###   ########.fr       */
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

void	fill_pt_arr(int fd, t_point **pt_arr)
{	
	char	*line;
	char	**split_line;
	char	**split_line_sav;
	int		row;
	int		col;
		
	row = 0;
	line = get_next_line(fd);	
	while (line)
	{
		col = 0;
		split_line = ft_split(line, ' ');		
		split_line_sav = split_line;
		while (*split_line && **split_line != '\n')
		{
			*pt_arr = (t_point *) malloc(sizeof(t_point)); //
			(*pt_arr)->x = col;
			(*pt_arr)->y = row;
			(*pt_arr)->z = ft_atoi(*split_line);
			pt_arr++;
			col++;
			split_line++;
		}
		row++;
		free(line);
		free(split_line_sav);
		line = get_next_line(fd);
	}	
}

int	open_file(char *argv[])
{
	int	fd;
	
	fd = open(*(argv + 1), O_RDONLY);
	if (fd < 0)
	{
		perror(*(argv + 1));
		return (0);
	}
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
void	free_ptr_arr(void **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}
void	input_handle(char *argv[])
{
	t_point	**pt_arr;
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
	{ 
		free(pt_arr);
		exit(1);
	}
	fill_pt_arr(fd, pt_arr);
	close(fd);
	print_pt_arr(pt_arr);
	free_ptr_arr((void **) pt_arr);
}

int	main(int argc, char *argv[])
{
	void	*mlx_connect;
	void	*mlx_window;

	if (argc != 2)
		return (1);	
	input_handle(argv);  // apres fd
	// mlx_connect = mlx_init(); // mlx // err...
	// mlx_window = mlx_new_window(mlx_connect, 500, 500, "fdf");
	// mlx_loop(mlx_connect);	
		
	// mlx_destroy_window(mlx_connect, mlx_window);
	// mlx_destroy_display(mlx_connect);
	// free(mlx_connect);	
	return (0);
}