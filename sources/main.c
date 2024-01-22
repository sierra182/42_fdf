/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/22 20:11:42 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "setup.h"
#include <math.h>

#include <stdio.h>
t_point	**input_handle(char *argv[]);

void	print_pt_arr(t_point *pt_arr[])
{
	while (*pt_arr)
	{	
		ft_printf("x: %d, y: %d, z:%d, w:%d, nx: %d, ny: %d, nz: %d, nw:%d\n",
			(*pt_arr)->init_vect[0], (*pt_arr)->init_vect[1], (*pt_arr)->init_vect[2], (*pt_arr)->init_vect[3],
				(*pt_arr)->new_vect[0], (*pt_arr)->new_vect[1], (*pt_arr)->new_vect[2], (*pt_arr)->new_vect[3]);	
		pt_arr++;
	}
	ft_printf("\n");
}

void	print_matrix(double matrix[][MTX])
{
	int	i;
	int	j;
	
	i = 0;
	while (i < MTX)
	{
		j = 0;
		while (j < MTX)
		{			
			printf("%f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	init_matrix(double matrix[][MTX])
{
	int	i;
	int	j;

	i = -1;
	while (++i < MTX)
	{
		matrix[i][i] = 1.0;
		j = -1;
		while (++j < MTX)		
			if (i != j)			
				matrix[i][j] = 0.0;	
	}
}

void	reset_matrix(t_point **pt_arr)
{	
	int i;

	while (*pt_arr)
	{
		i = 0;
		while (i < MTX)
			(*pt_arr)->new_vect[i++] = 0.0;		
		pt_arr++;
	}
}

void	apply_matrix(double matrix[][MTX], t_point **pt_arr)
{	
	int	i;
	int	j;
	
	reset_matrix(pt_arr);
	while (*pt_arr)
	{		
		i = -1;
		while (++i < MTX)
		{
			j = -1;
			while (++j < MTX)			
				(*pt_arr)->new_vect[i] += (int) (matrix[i][j]
					 * (*pt_arr)->init_vect[j]);				
		}
		pt_arr++;
	}
}
			
void	set_matrix_scale(double matrix[][MTX], double scale[])
{
	int	i;

	i = -1;
	while (++i < MTX - 1)
		matrix[i][i] = scale[i];	
}

void	set_matrix_translate(double matrix[][MTX], double trans[])
{
	int	i;
	
	i = -1;
	while (++i < MTX - 1)	
		matrix[i][MTX - 1] = trans[i];	
}

void	set_matrix_rotation(double matrix[][MTX], double angle, int *axe)
{
	angle *= M_PI / 180.0;	 
	if (axe[0])
	{		
		matrix[1][1] = cos(angle);
		matrix[1][2] = -sin(angle);
		matrix[2][1] = sin(angle);
		matrix[2][2] = cos(angle);	
	}
	else if (axe[1])
	{ 
		matrix[0][0] = cos(angle);
		matrix[0][2] = sin(angle);
		matrix[2][0] = -sin(angle);
		matrix[2][2] = cos(angle);
	}
	else if (axe[2])
	{
		matrix[0][0] = cos(angle);
		matrix[0][1] = -sin(angle);
		matrix[1][0] = sin(angle);
		matrix[1][1] = cos(angle);
	}
}

void	set_matrix_persp(double matrix[][MTX], double fov, double aspect, double z_near, double z_far)
{
	double f;
	//double z_len;
	(void) z_near;
	(void) z_far;
	f = 1; 
	if (tan(fov * M_PI / 360.0))
		f = 1.0 / tan(fov * M_PI / 360.0);	
//	z_len = z_far - z_near;
	matrix[0][0] = aspect * f; 
	matrix[1][1] = f;//1.0 / aspect * tan(fov * M_PI / 360.0);//
	matrix[2][2] = 1;//z_far / z_len; //(z_near + z_far) / (z_near - z_far);////   //  
	matrix[2][3] = 0;//-z_far * z_near / z_len;//-2 * z_far * z_near / z_len; //(2 * z_near * z_far) / (z_near - z_far);// ; 
	matrix[3][2] = -1.0;// -0.1
	matrix[MTX - 1][MTX - 1] = 0;	
}

double	multiply_rowbycol(double row[], double m2[][MTX], int col)
{
	double	rslt;
	int		i;
		
	rslt = 0;
	i = -1;
	while (++i < MTX)	
		rslt += row[i] * m2[i][col];	
	return (rslt);
}

void	multiply_matrix(double m1[][MTX], double m2[][MTX], double mf[][MTX])
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < MTX)
	{
		j = -1;
		while (++j < MTX)				
			mf[i][j] = multiply_rowbycol(m1[i], m2, j);	
	}
}
	
// void clear_screen()
// {
// 	int i;
// 	int	j;

// 	i = 0;
// 	while (i < 500)
// 	{
// 		j = 0;
// 		while (j < 500)
// 		{
// 			mlx_pixel_put(mlx_connect, mlx_window, i, j, *(int *)(unsigned char [4]){0, 0, 0, 255});
// 			j++;
// 		}
// 		i++;
// 	}	
// }
// void print_pixels(t_point **pt_arr)
// {
// 	while (*pt_arr)
// 	{
// 		//sleep(.5);
// 		//int		mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
// 		if ((*pt_arr)->z > 0)
// 			mlx_pixel_put(mlx_connect, mlx_window, (*pt_arr)->new_x, (*pt_arr)->new_y, *(int *)(unsigned char [4]){255, 255, 255, 255});
// 		if ((*pt_arr)->z == 0)
// 			mlx_pixel_put(mlx_connect, mlx_window, (*pt_arr)->new_x, (*pt_arr)->new_y, *(int *)(unsigned char [4]){255, 255, 255, 255});
// 		pt_arr++;
// 	}
// }

void	img_data_handle(void *img_ptr, char	**img_data, int *size_l, int *bpp)
{
	static char	*img_data_lcl;
	static int	size_l_lcl;
	static int	bpp_lcl;

	if (img_ptr)
		img_data_lcl = mlx_get_data_addr(img_ptr, &bpp_lcl, &size_l_lcl,
				&(int){0});
	else
	{
		*img_data = img_data_lcl;
		*size_l = size_l_lcl;
		*bpp = bpp_lcl;
	}
}

unsigned int	get_final_color(int *start, int *end, int z)
{
	float	factor;
	int		r;
	int		g;
	int		b;

	factor = (float)(z - 50) / (0 - 50);
	r = start[0] + factor * (end[0] - start[0]);
	g = start[1] + factor * (end[1] - start[1]);
	b = start[2] + factor * (end[2] - start[2]);
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

void	put_pxl(int x, int y, int z)
{
	unsigned int	final_color;
	char			*img_data;
	int				pxl_pos;
	int				bpp;
	int				size_line;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		final_color = get_final_color((int []){47, 175, 98},
				(int []){159, 165, 167}, z);
		img_data_handle(NULL, &img_data, &size_line, &bpp);
		pxl_pos = x * bpp / 8 + y * size_line;
		*(int *)(img_data + pxl_pos) = final_color;
	}
}

void	draw_line_action(t_draw_act *act)
{
	int	error;

	error = act->greater_delta;
	while (act->pos != act->pos_prim)
	{
		act->pos += act->dir;
		if (error <= 0)
		{
			act->opp_pos += act->opp_dir;
			error += act->greater_delta * 2;
		}
		if (!act->flag)		
			put_pxl(act->pos, act->opp_pos, act->z);
		else		
			put_pxl(act->opp_pos, act->pos, act->z);
		error -= act->lower_delta * 2;
	}
}

void	draw_line_setup(int **dir, int *delta, int pos_value_a, int pos_value_b)
{
	*dir[0] = *dir[1];
	*delta = pos_value_a - pos_value_b;
}

void	draw_line(double *vct, double *vct_prm)
{
	int	dx;
	int	dy;
	int	h_dir;
	int	v_dir;

	if ((int) vct[0] > (int) vct_prm[0])
		draw_line_setup((int *[]){&h_dir, &(int){-1}}, &dx, vct[0], vct_prm[0]);
	else
		draw_line_setup((int *[]){&h_dir, &(int){1}}, &dx, vct_prm[0], vct[0]);
	if ((int) vct[1] > (int) vct_prm[1])
		draw_line_setup((int *[]){&v_dir, &(int){-1}}, &dy, vct[1], vct_prm[1]);
	else
		draw_line_setup((int *[]){&v_dir, &(int){1}}, &dy, vct_prm[1], vct[1]);
	if (dx > dy)
		draw_line_action(&(t_draw_act){.greater_delta = dx, .lower_delta = dy,
			.pos = vct[0], .opp_pos = vct[1], .pos_prim = vct_prm[0],
			.dir = h_dir, .opp_dir = v_dir, .z = vct[2], .flag = 0});
	else
		draw_line_action(&(t_draw_act){.greater_delta = dy, .lower_delta = dx,
			.pos = vct[1], .opp_pos = vct[0], .pos_prim = vct_prm[1],
			.dir = v_dir, .opp_dir = h_dir, .z = vct[2], .flag = 1});
}


int 	get_line_length(t_point **pt_arr)
{
	int	len;
	
	len = 0;
	if (!*pt_arr)
		return (len);
	while (pt_arr[len] && !pt_arr[len]->line)	
		len++;
	return (++len);
}

int 	get_n_line(t_point **pt_arr)
{
	int	n;

	n = 0;
	if (!*pt_arr)
		return (n);
	while (*pt_arr)
		if ((*pt_arr++)->line == 1)
			n++;
	return (++n);
}
void	add_background(int x, int y)
{
	char			*img_data;
	int				pxl_pos;
	int				bpp;
	int				size_line;

	img_data_handle(NULL, &img_data, &size_line, &bpp);
	while (++x < WIDTH)
	{	
		y = -1;
		while (++y < HEIGHT)
		{
			pxl_pos = x * bpp / 8 + y * size_line;
			*(int *)(img_data + pxl_pos) = 0x373224;
		}
	}
}

void	print_img(t_point **pt_arr, int	per, t_mlx *mlx)
{	
	void	*img_ptr;
	int		len;
		
	img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	img_data_handle(img_ptr, NULL, NULL, NULL);
	add_background(-1, -1);
	len = get_line_length(pt_arr);//!!
	while (*pt_arr)
	{
		if ((*pt_arr)->line < 2 && (!per || ((*pt_arr)->init_vect[2] <= 0
				&& (*(pt_arr + len))->init_vect[2] <= 0)))
			draw_line((*pt_arr)->new_vect, (*(pt_arr + len))->new_vect);
		if ((!(*pt_arr)->line || (*pt_arr)->line == 2) && (!per
				|| ((*pt_arr)->init_vect[2] <= 0
				&& (*(pt_arr + 1))->init_vect[2] <= 0)))
			draw_line((*pt_arr)->new_vect, (*(pt_arr + 1))->new_vect);
		if ((*pt_arr)->line == 1)
			len = get_line_length(pt_arr + 1);
		pt_arr++;
	}
	mlx_put_image_to_window(mlx->connect, mlx->window, img_ptr, 0, 0);
	mlx_destroy_image(mlx->connect, img_ptr);
}

double	get_average(t_point **pt_arr, int axe)
{
	double	sum;
	int	i;

	i = -1;
	sum = 0.0;
	while (pt_arr[++i])	
		sum += pt_arr[i]->init_vect[axe];	
	if (i)	
		return (sum / i);
	return (0.0);
}
void	save_new_vect(t_point **pt_arr)
{	
	int	i;

	while (*pt_arr)
	{
		i = -1;
		while (++i < MTX - 1)
			(*pt_arr)->init_vect[i] = (*pt_arr)->new_vect[i];	
		pt_arr++;
	}
}
t_point **copy_points(t_point **pt_arr)
{
	t_point **copy;
	int		i;
	int		j;

	i = 0;
	while (pt_arr[i])	
		i++;	
	copy = (t_point **) ft_calloc(i + 1, sizeof(t_point *));
	i = 0;
	while (pt_arr[i])
	{
		copy[i] = malloc(sizeof(t_point));	
		copy[i]->init_vect[3] =  1 ;
		j = -1;
		while (++j < MTX)		
			copy[i]->new_vect[j] = pt_arr[i]->new_vect[j];
		copy[i]->line = pt_arr[i]->line;
		i++;		
	}
	return (copy);
}

double	get_initial_scale(t_point **pt_arr)
{
	double 	scale;	
	double	coef;
	int		line_len;
	int		n_line;
	
	coef = 0.75;
	n_line = get_n_line(pt_arr);
	line_len = get_line_length(pt_arr);
	if (line_len > n_line)		
		scale = coef * WIDTH / line_len;
	else
		scale = coef * HEIGHT / n_line;
	return (scale);
}

void	homogenize_pt_arr(t_point **pt_arr)
{
	int	i;

	while (*pt_arr)
	{
		i = 0;
		if ((*pt_arr)->new_vect[MTX - 1]) 
			while (i < 2)			
				(*pt_arr)->new_vect[i++] /= (*pt_arr)->new_vect[MTX - 1];
		pt_arr++;
	}
}

#include <unistd.h>

int	loop(void *param[])
{	
	t_point **pt_arr;
	t_event *event;
	t_mtrx 	*mtrx; 
		
	usleep(16670);
	event = (t_event *) param[2];
	if (!event->flag)
		return 0;
	pt_arr = (t_point **) param[0];
	mtrx = (t_mtrx *) param[1];
		
	set_matrix_scale(mtrx->scl, (double[]){event->scl, event->scl, event->scl});
	set_matrix_scale(mtrx->scl2, (double[]){1, 1, event->scl_z});
	set_matrix_scale(mtrx->scl3, (double[]){event->scl_end, event->scl_end, event->scl_end});
	set_matrix_rotation(mtrx->rtt_x, event->rx, (int []) {1, 0, 0});
	set_matrix_rotation(mtrx->rtt_y, event->ry, (int []) {0, 1, 0});
	set_matrix_rotation(mtrx->rtt_z, event->rz, (int []) {0, 0, 1});
	set_matrix_translate(mtrx->trs_lp, (double []) {event->tx, event->ty, event->tz});
	set_matrix_persp(mtrx->persp, event->persp, WIDTH / HEIGHT, event->znr, event->zfr);
	set_matrix_translate(mtrx->trs_cntr, (double []) {WIDTH / 2.0, HEIGHT / 2.0, HEIGHT / 1.5});	
	apply_matrix(mtrx->scl2, pt_arr);
	t_point **p_cpy = copy_points(pt_arr);
	save_new_vect(p_cpy);	
	multiply_matrix(mtrx->neutral, mtrx->trs_lp, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->rtt_y, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->rtt_x, mtrx->fnl_tmp);
    multiply_matrix(mtrx->fnl_tmp, mtrx->rtt_z, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->scl, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->trs_ori, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->neutral, mtrx->fnl_tmp);
	if (event->persp)	
	{
		multiply_matrix(mtrx->persp, mtrx->fnl_tmp, mtrx->fnl);	
		apply_matrix(mtrx->fnl, p_cpy);	
		homogenize_pt_arr(p_cpy);
		save_new_vect(p_cpy);	
		multiply_matrix(mtrx->trs_cntr, mtrx->scl3, mtrx->fnl);
		apply_matrix(mtrx->fnl, p_cpy);		 
		print_img(p_cpy, 1, (t_mlx *) param[3]);
		free_ptr_arr((void *) p_cpy);
		return (0);
	}
	multiply_matrix(mtrx->scl3, mtrx->fnl_tmp, mtrx->fnl);
	multiply_matrix(mtrx->trs_cntr, mtrx->fnl, mtrx->fnl_tmp);
	apply_matrix(mtrx->fnl_tmp, p_cpy);		
	print_img(p_cpy, 0, (t_mlx *) param[3]);
	free_ptr_arr((void *) p_cpy);
	event->flag = 0;
	return (0);
}

void	init_event(t_event *event, t_point **pt_arr)
{
	event->flag = 1;	
	event->rx = 0.0;
	event->ry = 0.0;
	event->rz = 0.0;
	event->tx = 0.0;
	event->ty = 0.0;
	event->tz = -HEIGHT / 1.5;
	event->scl = get_initial_scale(pt_arr);
	event->scl_z = 1.0;
	event->scl_end = 1.0;
	event->persp = 0.0;
	event->znr = 1.0;
	event->zfr = 100.0;
}

int key_press(int keycode, void *param[])
{
	t_event *event; 
		
    //printf("touche ton boyo: %d\n", keycode);	
	event = (t_event *) param[1];
	event->flag = 1;

	if (keycode == 120)
		event->rx++;
	else if (keycode == 99)
		event->rx--;
	else if (keycode == 121)
		event->ry++;
	else if (keycode == 117)
		event->ry--;	
	else if (keycode == 122)
		event->rz++;
	else if (keycode == 97)
		event->rz--;
	else if (keycode == 65432)
		event->scl_end += 0.1;
	else if (keycode == 65430)
		event->scl_end -= 0.1;
	else if (keycode == 115)
		event->scl += 1;
	else if (keycode == 100)
		event->scl -= 1;
	else if (keycode == 102)
		event->scl_z += 0.1;
	else if (keycode == 103)
		event->scl_z -= 0.1;
	else if (keycode == 65361)
		event->tx += 10;
	else if (keycode == 65363)
		event->tx -= 10;
	else if (keycode == 65362)
		event->ty += 10;
	else if (keycode == 65364)
		event->ty -= 10;
	else if (keycode == 65436)
		event->tz += 2;
	else if (keycode == 65438)
		event->tz -= 2;
	else if (keycode == 112)
		event->persp++;
	else if (keycode == 109)
		event->persp--;
	else if (keycode == 65431)
		event->znr++;
	else if (keycode == 65433)
		event->znr--;
	else if (keycode == 65432)
		event->zfr++;
	else if (keycode == 65430)
		event->zfr--;
	else if (keycode == 114)
		init_event(event, (t_point **) param[0]);
	else if (keycode == 65307)
		mlx_loop_end(param[2]);
    return 0;
}

int	clean_kill(t_point **pt_arr, t_mlx *mlx)
{
	free_ptr_arr((void **) pt_arr);
	mlx_destroy_window(mlx->connect, mlx->window);
	mlx_destroy_display(mlx->connect);
	free(mlx->connect);	
}

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
