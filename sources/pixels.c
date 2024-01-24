/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:18:16 by seblin            #+#    #+#             */
/*   Updated: 2024/01/24 12:17:10 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixels.h"

static void	img_data_handle(void *img_ptr, char	**img_data, int *size_l,
	int *bpp)
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

static unsigned int	get_final_color(int z)
{
	if (z > 5)
		return (250 << 16 | 142 << 8 | 115);
	else
		return (47 << 16 | 175 << 8 | 98);
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
		final_color = get_final_color(z);
		img_data_handle(NULL, &img_data, &size_line, &bpp);
		pxl_pos = x * bpp / 8 + y * size_line;
		*(int *)(img_data + pxl_pos) = final_color;
	}
}

static void	add_background(int x, int y)
{
	char	*img_data;
	int		pxl_pos;
	int		bpp;
	int		size_line;

	img_data_handle(NULL, &img_data, &size_line, &bpp);
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			pxl_pos = x * bpp / 8 + y * size_line;
			*(int *)(img_data + pxl_pos) = 0xF0DEB4;
		}
	}
}

void	print_img(t_point **pt_arr, int per, t_mlx *mlx)
{
	void	*img_ptr;
	int		len;

	img_ptr = mlx_new_image(mlx->connect, WIDTH, HEIGHT);
	img_data_handle(img_ptr, NULL, NULL, NULL);
	add_background(-1, -1);
	len = get_line_length(pt_arr);
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
