/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/08 07:56:43 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include "mlx.h"

#include <unistd.h>



int	**create_matrix(int fd)
{
	char	**matrix;
	char	*line;
	int		rows;
	int		cols;
	int		i;
	
	rows = 0;
	cols = 0;
	line = get_next_line(fd);
	cols = (int) ft_wc(line);
	while (line)
	{
		line = get_next_line(fd);
		rows++;
	}	
	matrix = (int **) malloc(rows * sizeof(int *));
	i = 0;
	while (i < rows)	
		matrix[i++] = (int *) malloc(cols * sizeof(int));
	return (matrix);
}


void	input_handle(char *argv[])
{
	int		fd;
	char	*line;
	int		**matrix;
	int		rows;
	int		cols;
	int		i;
	
	fd = open(*(argv + 1), O_RDONLY);
	if (fd < 0)
		return (perror(*(argv + 1)), exit(1));	 // fd*
	
	
	line = "";
	// while (line)
	// {
	// 	line = get_next_line(fd);
	// 	split_line = ft_split(line);
	// 	while (split_line)
	// 		matrix[ft_atoi(line);
	// }	
	
}

int	main(int argc, char *argv[])
{
	void	*mlx_connect;
	void	*mlx_window;

	if (argc != 2)
		return (1);
	//input_handle();  // apres fd
	mlx_connect = mlx_init(); // mlx // err...
	mlx_window = mlx_new_window(mlx_connect, 500, 500, "fdf");
	mlx_loop(mlx_connect);	
		
	mlx_destroy_window(mlx_connect, mlx_window);
	mlx_destroy_display(mlx_connect);
	free(mlx_connect);	
	return (0);
}