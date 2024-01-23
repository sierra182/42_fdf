/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/23 12:20:33 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	launch_matrix(t_point **pt_arr, t_mlx *mlx)
{	
	t_mtrx 	mtrx;
	t_event event;
		
	init_event(&event, pt_arr);
	init_matrix(mtrx.neutral);
	init_matrix(mtrx.persp);
	init_matrix(mtrx.scl);
	init_matrix(mtrx.scl2);
	init_matrix(mtrx.scl3);
	init_matrix(mtrx.trs_ori); 
	init_matrix(mtrx.trs_ori2);
	init_matrix(mtrx.trs_cntr);
	init_matrix(mtrx.trs_lp);
	init_matrix(mtrx.rtt_x);
	init_matrix(mtrx.rtt_y);
	init_matrix(mtrx.rtt_z);			
	set_matrix_translate(mtrx.trs_ori, (double []) {-get_average(pt_arr, 0), 
													-get_average(pt_arr, 1), 
														-get_average(pt_arr, 2)}); 
	mlx_hook(mlx->window, 2, 1L << 0, key_press, (void *[]){pt_arr, &event, mlx->connect});	
	mlx_hook(mlx->window, 17, 0L, mlx_loop_end, mlx->connect);	
	mlx_loop_hook(mlx->connect, loop, (void *[]){pt_arr, &mtrx, &event, mlx});
	mlx_loop(mlx->connect);
}

int	clean_kill(t_point **pt_arr, t_mlx *mlx)
{
	free_ptr_arr((void **) pt_arr);
	mlx_destroy_window(mlx->connect, mlx->window);
	mlx_destroy_display(mlx->connect);
	free(mlx->connect);	
}

int	main(int argc, char *argv[])
{
	t_point	**pt_arr;
	t_mlx 	mlx;
	
	if (argc != 2)
		return (1);
	pt_arr = input_handle(argv);
	mlx.connect = mlx_init();
	if (!mlx.connect)
		return (free_ptr_arr((void **) pt_arr), 1);
	mlx.window = mlx_new_window(mlx.connect, WIDTH, HEIGHT, "fdf");
	if (!mlx.window)
		return (free_ptr_arr((void **) pt_arr),
			mlx_destroy_display(mlx.connect), free(mlx.connect), 1);	
	launch_matrix(pt_arr, &mlx);
	clean_kill(pt_arr, &mlx);
	return (0);
}
