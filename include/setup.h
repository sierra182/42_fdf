/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 07:55:53 by svidot            #+#    #+#             */
/*   Updated: 2024/01/24 10:39:37 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# define WIDTH 1000
# define HEIGHT 600
# define MTX 4
# define M_PI 3.14159265358979323846

typedef struct s_mlx
{
	void	*connect;
	void	*window;
}	t_mlx;

typedef struct s_point
{
	double	init_vect[MTX];
	double	new_vect[MTX];
	int		line;
}	t_point;

typedef struct s_matrix
{
	double	neutral[MTX][MTX];
	double	persp[MTX][MTX];
	double	scl[MTX][MTX];
	double	scl2[MTX][MTX];
	double	scl3[MTX][MTX];
	double	trs_ori[MTX][MTX];
	double	trs_ori2[MTX][MTX];
	double	trs_cntr[MTX][MTX];
	double	trs_lp[MTX][MTX];
	double	rtt_x[MTX][MTX];
	double	rtt_y[MTX][MTX];
	double	rtt_z[MTX][MTX];
	double	fnl[MTX][MTX];
	double	fnl_tmp[MTX][MTX];
}	t_mtrx;

typedef struct s_event
{
	int		flag;
	double	rx;
	double	ry;
	double	rz;
	double	tx;
	double	ty;
	double	tz;
	double	scl;
	double	scl_z;
	double	scl_end;
	double	persp;
}	t_event;

typedef struct s_draw_act
{
	int	greater_delta;
	int	lower_delta;
	int	pos;
	int	opp_pos;
	int	pos_prim;
	int	dir;
	int	opp_dir;
	int	z;
	int	flag;
}	t_draw_act;

#endif
