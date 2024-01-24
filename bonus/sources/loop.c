/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:21:41 by seblin            #+#    #+#             */
/*   Updated: 2024/01/24 09:34:08 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	set_multiply_matrix(t_mtrx *mtrx, t_point **pt_cpy)
{
	multiply_matrix(mtrx->neutral, mtrx->rtt_z, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->scl, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->trs_ori, mtrx->fnl);
	apply_matrix(mtrx->fnl, pt_cpy);
	save_new_vect(pt_cpy);
	apply_matrix(mtrx->rtt_x, pt_cpy);
	save_new_vect(pt_cpy);
	multiply_matrix(mtrx->neutral, mtrx->trs_lp, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->rtt_y, mtrx->fnl);
}

static void	set_matrix_transform(t_mtrx *mtrx, t_event *event)
{
	set_matrix_scale(mtrx->scl, (double []){event->scl, event->scl,
		event->scl});
	set_matrix_scale(mtrx->scl2, (double []){1, 1, event->scl_z});
	set_matrix_scale(mtrx->scl3, (double []){event->scl_end,
		event->scl_end, event->scl_end});
	set_matrix_rotation(mtrx->rtt_x, event->rx, (int []){1, 0, 0});
	set_matrix_rotation(mtrx->rtt_y, event->ry, (int []){0, 1, 0});
	set_matrix_rotation(mtrx->rtt_z, event->rz, (int []){0, 0, 1});
	set_matrix_translate(mtrx->trs_lp, (double []){event->tx,
		event->ty, event->tz});
	set_matrix_translate(mtrx->trs_cntr, (double []){WIDTH / 2.0,
		HEIGHT / 2.0, HEIGHT / 1.5});
	set_matrix_persp(mtrx->persp, event->persp, WIDTH / HEIGHT);
}

static void	persp_handle(t_event *event, t_mtrx *mtrx, t_point **pt_cpy,
t_mlx *mlx)
{
	if (event->persp)
	{
		multiply_matrix(mtrx->persp, mtrx->fnl, mtrx->fnl_tmp);
		apply_matrix(mtrx->fnl_tmp, pt_cpy);
		homogenize_pt_arr(pt_cpy);
		save_new_vect(pt_cpy);
		multiply_matrix(mtrx->trs_cntr, mtrx->scl3, mtrx->fnl_tmp);
		apply_matrix(mtrx->fnl_tmp, pt_cpy);
		print_img(pt_cpy, 1, mlx);
	}
	else
	{
		multiply_matrix(mtrx->scl3, mtrx->fnl, mtrx->fnl_tmp);
		multiply_matrix(mtrx->trs_cntr, mtrx->fnl_tmp, mtrx->fnl);
		apply_matrix(mtrx->fnl, pt_cpy);
		print_img(pt_cpy, 0, mlx);
	}
}

int	loop(void *param[])
{
	static int	refresh;
	t_point		**pt_arr;
	t_point		**pt_cpy;
	t_event		*event;
	t_mtrx		*mtrx;

	refresh = (refresh + 1) % 100;
	event = (t_event *) param[2];
	if (!event->flag && refresh)
		return (0);
	pt_arr = (t_point **) param[0];
	mtrx = (t_mtrx *) param[1];
	set_matrix_transform(mtrx, event);
	apply_matrix(mtrx->scl2, pt_arr);
	pt_cpy = copy_points(pt_arr);
	save_new_vect(pt_cpy);
	set_multiply_matrix(mtrx, pt_cpy);
	persp_handle(event, mtrx, pt_cpy, param[3]);
	free_ptr_arr((void *) pt_cpy);
	event->flag = 0;
	return (0);
}
