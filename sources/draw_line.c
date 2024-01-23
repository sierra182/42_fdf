/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:07:04 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 12:00:11 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	put_pxl(int x, int y, int z);
#include "setup.h"

static void	draw_line_action(t_draw_act *act)
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

static void	draw_line_setup(int **dir, int *delta, int pos_value_a, int pos_value_b)
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