/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:21:41 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 19:55:52 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	set_multiply_matrix(t_mtrx *mtrx)
{
	multiply_matrix(mtrx->neutral, mtrx->trs_lp, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->rtt_y, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->rtt_x, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->rtt_z, mtrx->fnl);
	multiply_matrix(mtrx->fnl, mtrx->scl, mtrx->fnl_tmp);
	multiply_matrix(mtrx->fnl_tmp, mtrx->trs_ori, mtrx->fnl);
}

static void	set_matrix_transform(t_mtrx *mtrx, t_event *event)
{
	set_matrix_scale(mtrx->scl, (double []){event->scl, event->scl, 1});
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

static void	persp_handle(t_point **pt_arr, t_mtrx *mtrx, t_point **pt_cpy,
t_mlx *mlx)
{
	int	i;

	multiply_matrix(mtrx->scl3, mtrx->fnl, mtrx->fnl_tmp);
	multiply_matrix(mtrx->trs_cntr, mtrx->fnl_tmp, mtrx->fnl);
	apply_matrix(mtrx->fnl, pt_cpy);
	i = -1;
	while (pt_arr[++i])
		pt_cpy[i]->new_vect[3] = pt_arr[i]->init_vect[2];
	print_img(pt_cpy, 0, mlx);	
}

int	loop(void *param[])
{
	static int	refresh;
	t_point		**pt_arr;
	t_point		**pt_cpy;
	t_event		*event;
	t_mtrx		*mtrx;

	usleep(16670);
	refresh = (refresh + 1) % 80;
	event = (t_event *) param[2];
	if (!event->flag && refresh)
		return (0);
	pt_arr = (t_point **) param[0];
	mtrx = (t_mtrx *) param[1];
	set_matrix_transform(mtrx, event);
	apply_matrix(mtrx->scl2, pt_arr);
	pt_cpy = copy_points(pt_arr);
	save_new_vect(pt_cpy);
	set_multiply_matrix(mtrx);
	persp_handle(pt_arr, mtrx, pt_cpy, param[3]);
	free_ptr_arr((void *) pt_cpy);
	event->flag = 0;
	return (0);
}
