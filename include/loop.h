/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:37:26 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 23:02:38 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H
# include "setup.h"
# include "libft.h"

void	multiply_matrix(double m1[][MTX], double m2[][MTX], double mf[][MTX]);
void	apply_matrix(double matrix[][MTX], t_point **pt_arr);
void	save_new_vect(t_point **pt_arr);
t_point	**copy_points(t_point **pt_arr);
void	homogenize_pt_arr(t_point **pt_arr);
void	set_matrix_persp(double matrix[][MTX], double fov, double aspect);
void	set_matrix_rotation(double matrix[][MTX], double angle, int *axe);
void	set_matrix_translate(double matrix[][MTX], double trans[]);
void	set_matrix_scale(double matrix[][MTX], double scale[]);
void	print_img(t_point **pt_arr, int per, t_mlx *mlx);

#endif