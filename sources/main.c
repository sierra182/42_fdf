/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/18 09:48:13 by svidot           ###   ########.fr       */
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
		matrix[i][i] = 1;
		j = -1;
		while (++j < MTX)		
			if (i != j)			
				matrix[i][j] = 0;	
	}
}

void	reset_matrix(t_point **pt_arr)
{	
	int i;

	while (*pt_arr)
	{
		i = 0;
		while (i < MTX)
			(*pt_arr)->new_vect[i++] = 0;		
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
// void	apply_m(t_point **pt_arr)
// {		
// 	while (*pt_arr)
// 	{
// 		(*pt_arr)->x = (*pt_arr)->new_x;
// 		(*pt_arr)->y = (*pt_arr)->new_y;
// 		(*pt_arr)->z = (*pt_arr)->new_z;
// 		pt_arr++;
// 	}
// }
			
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
	double z_len;
	
	z_len = z_far - z_near;
	f = 1.0 / tan(fov * M_PI / 360.0);	
	matrix[0][0] = aspect * f; 
	matrix[1][1] = f;//1.0 / aspect * tan(fov * M_PI / 360.0);//
	matrix[2][2] = z_far / z_len; //(z_near + z_far) / (z_near - z_far);////   //  
	matrix[2][3] = -z_far * z_near / z_len; //(2 * z_near * z_far) / (z_near - z_far);// ; 
	matrix[3][2] = 1.0;// -0.1
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

void	put_pxl(int x, int y, int z, char *img_data, int bpp, int size_line)
{
	int	pxl_pos;
	
	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pxl_pos = (x * bpp / 8 + y * size_line);
		if (!z)
			*(int *)(img_data + pxl_pos) = 0x00FF0000;
		else if (z < 0)
			*(int *)(img_data + pxl_pos) = 0x0000FF00;
		else
			*(int *)(img_data + pxl_pos) = 0x000000FF;
	}
}

void	draw_line_action(int greater_delta, int lower_delta, int pos, int opp_pos, int pos_prime, int dir, int opp_dir, int z, char *img_data, int bpp, int size_line, int flag)
{
	int error;
	
	error = greater_delta;	
	while (pos != pos_prime)
	{
		pos += dir;
		if (error <= 0)
		{
			opp_pos += opp_dir;
			error += greater_delta * 2;
		}
		if (!flag)		
			put_pxl(pos, opp_pos, z, img_data, bpp, size_line);
		else
			put_pxl(opp_pos, pos, z, img_data, bpp, size_line);
		error -= lower_delta * 2;
	}
}

void	draw_line_setup(int *dir, int dir_value, int *delta, int pos_value_a, int pos_value_b )
{
	*dir = dir_value;
	*delta = pos_value_a - pos_value_b;
}

void	draw_line(int x, int y, int z, int xp, int yp, char *img_data, int bpp, int size_line)
{
	int	dx;
	int dy;	
	int h_dir;
	int v_dir;
	
	if (x > xp)	
		draw_line_setup(&h_dir, -1, &dx, x, xp);	
	else
		draw_line_setup(&h_dir, 1, &dx, xp, x);	
	if (y > yp)
		draw_line_setup(&v_dir, -1, &dy, y, yp);	
	else
		draw_line_setup(&v_dir, 1, &dy, yp, y);
	if (dx > dy)	
		draw_line_action(dx, dy, x, y, xp, h_dir, v_dir, z, img_data, bpp, size_line, 0);	
	else	
		draw_line_action(dy, dx, y, x, yp, v_dir, h_dir, z, img_data, bpp, size_line, 1);   		
}

void *mlx_connect;
void *mlx_window;

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

void	print_img(t_point **pt_arr)
{
	void *img_ptr;
	char *img_data;
    int bpp; 
    int size_line;
  	int pxl_pos;
	int truc = 0;//200;	
	
	img_ptr = mlx_new_image(mlx_connect, WIDTH, HEIGHT);	
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &(int){0});
	t_point **pt_arr_sav = pt_arr;
	while (*pt_arr)
	{
		if ((*pt_arr)->new_vect[0] + truc >= 0 && (*pt_arr)->new_vect[0] + truc <= WIDTH && (*pt_arr)->new_vect[1] + truc >= 0 && (*pt_arr)->new_vect[1] + truc <= HEIGHT)
		{			
			pxl_pos = (((*pt_arr)->new_vect[1] + truc) * size_line) + (((*pt_arr)->new_vect[0] + truc) * (bpp / 8));
			if ((*pt_arr)->init_vect[2])  		
				*(int *)(img_data + pxl_pos) = 0xFFFFFFFF;
			else
				*(int *)(img_data + pxl_pos) = 0xFFFFFFFF;
		}
		pt_arr++;
	}	
	int len = get_line_length(pt_arr_sav);// printf("%d\n", len);
	while (*pt_arr_sav)
	{
		if ((*pt_arr_sav)->line < 2)// && get_line_length(pt_arr_sav + 1) >= )		
			draw_line((*pt_arr_sav)->new_vect[0], (*pt_arr_sav)->new_vect[1], (*pt_arr_sav)->new_vect[2], (*(pt_arr_sav + len))->new_vect[0], (*(pt_arr_sav + len))->new_vect[1], img_data, bpp, size_line);
		if (!(*pt_arr_sav)->line || (*pt_arr_sav)->line == 2)	
			draw_line((*pt_arr_sav)->new_vect[0], (*pt_arr_sav)->new_vect[1], (*pt_arr_sav)->new_vect[2], (*(pt_arr_sav + 1))->new_vect[0], (*(pt_arr_sav + 1))->new_vect[1], img_data, bpp, size_line);
		if ((*pt_arr_sav)->line == 1)
		  	len = get_line_length(pt_arr_sav + 1);
		// if ((*pt_arr_sav)->line)
		//  	len = get_line_length(pt_arr_sav + 1);	
		pt_arr_sav++;	
	}
	mlx_put_image_to_window(mlx_connect, mlx_window, img_ptr, 0, 0);
	mlx_destroy_image(mlx_connect, img_ptr);
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

t_point **copy_points(t_point **pt_arr)
{
	int		i;	
	t_point **copy;
	t_point **pt_arr_sav = pt_arr;
	
	i = 0;
	while (*pt_arr)
	{
		i++;
		pt_arr++;
	}
	pt_arr = pt_arr_sav;
	copy = (t_point **) ft_calloc(i + 1, sizeof(t_point *));
	i = 0;
	while (*pt_arr)
	{
		copy[i] = malloc(sizeof(t_point));
		copy[i]->init_vect[0] = (*pt_arr)->init_vect[0];
		copy[i]->init_vect[1] = (*pt_arr)->init_vect[1];
		copy[i]->init_vect[2] = (*pt_arr)->init_vect[2];
		copy[i]->init_vect[3] = (*pt_arr)->init_vect[3];
		copy[i]->new_vect[0] = (*pt_arr)->new_vect[0];
		copy[i]->new_vect[1] = (*pt_arr)->new_vect[1];
		copy[i]->new_vect[2] = (*pt_arr)->new_vect[2];
		copy[i]->new_vect[3] = (*pt_arr)->new_vect[3];
		copy[i]->line = (*pt_arr)->line;
		i++;
		pt_arr++;
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
// void	homogenize_pt_arr(t_point **pt_arr)
// {
// 	int	i;

// 	while (*pt_arr)
// 	{
// 		i = 0;
// 		if ((*pt_arr)->init_vect[2])//if ((*pt_arr)->new_vect[3]) //
// 			while (i < MTX - 1)			
// 				(*pt_arr)->new_vect[i++] /= (*pt_arr)->init_vect[2];//(*pt_arr)->new_vect[i++] /= (*pt_arr)->new_vect[3];//
// 		pt_arr++;
// 	}
// }

void	homogenize_pt_arr(t_point **pt_arr)
{
	int	i;

	while (*pt_arr)
	{
		i = 0;
		if ((*pt_arr)->new_vect[MTX - 1]) 
			while (i < MTX - 1)			
				(*pt_arr)->new_vect[i++] /= (*pt_arr)->new_vect[MTX - 1];
		pt_arr++;
	}
}
#include <unistd.h>

double	m_neutral[MTX][MTX];
double	m_persp[MTX][MTX];
double	m_scl[MTX][MTX];
double	m_trs_ori[MTX][MTX];
double	m_trs_cntr[MTX][MTX];
double	m_trs_lp[MTX][MTX];
double	m_rtt_x[MTX][MTX];
double	m_rtt_y[MTX][MTX];
double	m_rtt_z[MTX][MTX];
double	m_fnl[MTX][MTX];
double	m_fnl_tmp[MTX][MTX];

double	scale;
double	x = 0;
double 	y = 0;
double 	z = 0;
double 	tx = 0;
double 	ty = 0;
double 	tz = 0;
double 	scale_z = 0.0;
double 	per = 0;

void	reset(void)
{	
	x = 0;
 	y = 0;
 	z = 0;
 	tx = 0;
 	ty = 0;
 	tz = 0;
 	scale_z = 0.0;
 	per = 0;
}

int	loop(t_point **pt_arr)
{	
	usleep(16670);
	set_matrix_scale(m_scl, (double[]){scale, scale, scale_z});
	set_matrix_rotation(m_rtt_y, y, (int []) {0, 1, 0});
	set_matrix_rotation(m_rtt_x, x, (int []) {1, 0, 0});
	set_matrix_rotation(m_rtt_z, z, (int []) {0, 0, 1});
	set_matrix_translate(m_trs_lp, (double []) {tx, ty, tz});
	set_matrix_persp(m_persp, per, WIDTH / HEIGHT, 1.0, 350000.0);

	// multiply_matrix(m_neutral, m_persp, m_fnl_tmp);
	// multiply_matrix(m_fnl_tmp, m_trs_cntr, m_fnl); //printf("scale z: %f", scale_z);// print_matrix(m_fnl_tmp);
	// multiply_matrix(m_fnl, m_trs_lp, m_fnl_tmp);
	// multiply_matrix(m_fnl_tmp, m_rtt_x, m_fnl);
	// multiply_matrix(m_fnl, m_rtt_y, m_fnl_tmp);
	// multiply_matrix(m_fnl_tmp, m_rtt_z, m_fnl);
	// multiply_matrix(m_fnl, m_scl, m_fnl_tmp);
	

	multiply_matrix(m_neutral, m_trs_lp, m_fnl);	
	multiply_matrix(m_fnl, m_trs_cntr, m_fnl_tmp);
    multiply_matrix(m_fnl_tmp, m_rtt_y, m_fnl);
	multiply_matrix(m_fnl, m_rtt_x, m_fnl_tmp); //printf("scale z: %f", scale_z);// print_matrix(m_fnl_tmp);
	if (per)	
	{
		multiply_matrix(m_neutral, m_fnl_tmp, m_fnl);	
		multiply_matrix(m_persp, m_fnl, m_fnl_tmp);	
	}
    multiply_matrix(m_fnl_tmp, m_rtt_z, m_fnl);
	multiply_matrix(m_fnl, m_scl, m_fnl_tmp);
	multiply_matrix(m_fnl_tmp, m_trs_ori, m_fnl);
 //	t_point ** cpy = copy_points(pt_arr);
	apply_matrix(m_fnl, pt_arr);
	homogenize_pt_arr(pt_arr);
	//	print_pt_arr(pt_arr);
	print_img(pt_arr);	
	return (0);
}

int key_press_function(int keycode, void *param)
{
    printf("touche ton boyo: %d\n", keycode);
	printf("scale z: %f, tz: %f, per: %f\n", scale_z, tz, per);
	if (keycode == 121)
		y++;
	else if (keycode == 117)
		y--;
	else if (keycode == 120)
		x++;
	else if (keycode == 99)
		x--;
	else if (keycode == 122)
		z++;
	else if (keycode == 97)
		z--;
	else if (keycode == 115)
		scale++;
	else if (keycode == 100)
		scale--;
	else if (keycode == 102)
		scale_z += .1;
	else if (keycode == 103)
		scale_z -= .1;
	else if (keycode == 65361)
		tx += 10;
	else if (keycode == 65363)
		tx -= 10;
	else if (keycode == 65362)
		ty += 10;
	else if (keycode == 65364)
		ty -= 10;
	else if (keycode == 65436)
		tz += 2;
	else if (keycode == 65438)
		tz -= 2;
	else if (keycode == 112)
		per++;
	else if (keycode == 109)
		per--;
	else if (keycode == 114)
		reset();	
    return 0;
}

void	global_matrix(t_point **pt_arr)
{	
	init_matrix(m_neutral);
	init_matrix(m_persp);
	init_matrix(m_scl); 
	init_matrix(m_trs_ori); 
	init_matrix(m_trs_cntr);
	init_matrix(m_trs_lp);
	init_matrix(m_rtt_x); 
	init_matrix(m_rtt_y);
	init_matrix(m_rtt_z);
	
	scale = get_initial_scale(pt_arr); 		
	set_matrix_translate(m_trs_ori, (double []) {-get_average(pt_arr, 0), 
													-get_average(pt_arr, 1), 
														-get_average(pt_arr, 2)}); 
	set_matrix_translate(m_trs_cntr,  (double []) {WIDTH / 2, HEIGHT / 2, 0.0}); 

	mlx_hook(mlx_window, 2, 1L << 0, key_press_function, NULL);
	mlx_loop_hook(mlx_connect, loop, pt_arr);
	mlx_loop(mlx_connect);	
}

int	main(int argc, char *argv[])
{
	t_point	**pt_arr;

	if (argc != 2)
		return (1);
	pt_arr = input_handle(argv);
	mlx_connect = mlx_init();
	if (!mlx_connect)
		return (free_ptr_arr((void **) pt_arr), 1);
	mlx_window = mlx_new_window(mlx_connect, WIDTH, HEIGHT, "fdf");
	if (!mlx_window)
		return (free_ptr_arr((void **) pt_arr),
			mlx_destroy_display(mlx_connect), free(mlx_connect), 1);
	
	global_matrix(pt_arr);

	free_ptr_arr((void **) pt_arr);
	mlx_destroy_window(mlx_connect, mlx_window);
	mlx_destroy_display(mlx_connect);
	free(mlx_connect);
	return (0);
}
