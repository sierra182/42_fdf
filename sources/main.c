/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/08 22:00:58 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "setup.h"

t_point	**input_handle(char *argv[]);

void	print_pt_arr(t_point *pt_arr[])
{
	while (*pt_arr)
	{
		ft_printf("x: %d, y: %d, z:%d, nx: %d, ny: %d\n", (*pt_arr)->x, (*pt_arr)->y, (*pt_arr)->z, (*pt_arr)->new_x, (*pt_arr)->new_y);
		pt_arr++;
	}
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
	
	print_pt_arr(pt_arr);
	
	while (*pt_arr)
	{
		//int		mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
		if ((*pt_arr)->z > 0)
			mlx_pixel_put(mlx_connect, mlx_window, (*pt_arr)->x, (*pt_arr)->y, *(int *)(unsigned char [4]){255, 0, 0, 255});	
		pt_arr++;
	}

	mlx_loop(mlx_connect);

	free_ptr_arr((void **) pt_arr);
	mlx_destroy_window(mlx_connect, mlx_window);
	mlx_destroy_display(mlx_connect);
	free(mlx_connect);
	return (0);
}
