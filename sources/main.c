/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/10 15:27:53 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "setup.h"
#include <math.h>

t_point	**input_handle(char *argv[]);

void	print_pt_arr(t_point *pt_arr[])
{
	while (*pt_arr)
	{
		if ((*pt_arr)->z > 0)
			ft_printf("x: %d, y: %d, z:%d, nx: %d, ny: %d, nz: %d\n", 
				(*pt_arr)->x, (*pt_arr)->y, (*pt_arr)->z, (*pt_arr)->new_x, (*pt_arr)->new_y, (*pt_arr)->new_z);
		pt_arr++;
	}
	ft_printf("\n");
}

#define MTX 4

void	init_matrix(double matrix[][MTX])
{
	int	i;
	int	j;

	i = 0;
	while (i < MTX)
	{
		j = 0;
		while (j < MTX)
		{
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	apply_matrix(double matrix[][MTX], t_point	**pt_arr)
{
	const int coef_t = matrix[MTX - 1][MTX - 1];
	int	i;
	int	j;
	
	while (*pt_arr)
	{
		i = 0;
		while (i < MTX - 1)
		{
			j = 0;
			while (j < MTX - 1)
			{
				if (i == 0)
					(*pt_arr)->new_x += matrix[i][j] * (*pt_arr)->x;									
				if (i == 1)
					(*pt_arr)->new_y += matrix[i][j] * (*pt_arr)->y;
				if (i == 2)
					(*pt_arr)->new_z += matrix[i][j] * (*pt_arr)->z;
				j++;
			}
			i++;
		}
		(*pt_arr)->new_x += matrix[0][j] * coef_t;
		(*pt_arr)->new_y += matrix[1][j] * coef_t;
		(*pt_arr)->new_z += matrix[2][j] * coef_t;
		pt_arr++;
	}
}

void	set_matrix_scale(double matrix[][MTX], double scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < MTX - 1)
	{
		j = 0;
		while (j < MTX - 1)
		{
			if (i == j)
				matrix[i][j] = scale;			
			j++;
		}
		i++;
	}
}

void	create_matrix_scale(t_point	**pt_arr)
{
	double	m_scl[MTX][MTX];
	
	init_matrix(m_scl);
	set_matrix_scale(m_scl, 20.0);
	apply_matrix(m_scl, pt_arr);	
}

void	set_matrix_translate(double matrix[][MTX], double x, double y, double z)
{
	matrix[0][MTX - 1] = x;
	matrix[1][MTX - 1] = y;
	matrix[2][MTX - 1] = z;
}

void	set_matrix_rotation(double matrix[][MTX], double angle, int *axe)
{
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

void	create_matrix_translate(t_point	**pt_arr)
{
	double	m_trs[MTX][MTX];

	init_matrix(m_trs);
	set_matrix_translate(m_trs, 0.0, 250.0, 0.0);
	apply_matrix(m_trs, pt_arr);
}

double	multiply_rowbycol(double row[], double m2[][MTX], int col)
{
	double	rslt;
	int		i;
	int		j;
	
	rslt = 0;
	i = 0;
	while (i < MTX)
	{
		rslt += row[i] * m2[i][col];
		i++;
	}
	return (rslt);
}

void	merge_matrix(double m1[][MTX], double m2[][MTX], double mf[][MTX])
{
	int	i;
	int	j;
	
	i = 0;
	while (i < MTX)
	{
		j = 0;
		while (j < MTX)
		{			
			mf[i][j] = multiply_rowbycol(m1[i], m2, j);
			j++;
		}
		i++;
	}

}

void	printf_matrix(double matrix[][MTX])
{
	int	i;
	int	j;
	
	i = 0;
	while (i < MTX)
	{
		j = 0;
		while (j < MTX)
		{			
			ft_printf("%f ", matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	global_matrix(t_point **pt_arr)
{
	double	m_scl[MTX][MTX];
	double	m_trs[MTX][MTX];
	double	m_rtt[MTX][MTX];
	double	m_fnl[MTX][MTX];
	double	m_fnl_tmp[MTX][MTX];
	
	init_matrix(m_scl); printf_matrix(m_scl);
	init_matrix(m_trs); printf_matrix(m_trs);
	init_matrix(m_rtt); //printf_matrix(m_rtt);
	set_matrix_scale(m_scl, 10); printf_matrix(m_scl);
	set_matrix_translate(m_trs, 100.0, 100.0, 0.0); printf_matrix(m_trs);
	set_matrix_rotation(m_rtt, 1.0, (int []) {0, 0, 1});
	merge_matrix( m_trs, m_rtt, m_fnl); printf_matrix(m_fnl);
		
	//set_matrix_translate(m_trs, 10.0, 0.0, 0.0); printf_matrix(m_trs);
//	merge_matrix(m_fnl_tmp, m_rtt, m_fnl); printf_matrix(m_fnl);
	apply_matrix(m_fnl, pt_arr);	
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
	global_matrix(pt_arr);
	//create_matrix_scale(pt_arr);
	//print_pt_arr(pt_arr);
	//create_matrix_translate(pt_arr);
	print_pt_arr(pt_arr);
	while (*pt_arr)
	{
		//int		mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
		if ((*pt_arr)->z > 0)
			mlx_pixel_put(mlx_connect, mlx_window, (*pt_arr)->new_x, (*pt_arr)->new_y, *(int *)(unsigned char [4]){255, 0, 0, 255});
		pt_arr++;
	}

	mlx_loop(mlx_connect);

	free_ptr_arr((void **) pt_arr);
	mlx_destroy_window(mlx_connect, mlx_window);
	mlx_destroy_display(mlx_connect);
	free(mlx_connect);
	return (0);
}
