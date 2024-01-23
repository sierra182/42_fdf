/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:18:06 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 12:19:47 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "setup.h"

t_point	**input_handle(char *argv[]);
int 	key_press(int keycode, void *param[]);
int		loop(void *param[]);
void	set_matrix_translate(double matrix[][MTX], double trans[]);
void	init_matrix(double matrix[][MTX]);
void	init_event(t_event *event, t_point **pt_arr);
double	get_average(t_point **pt_arr, int axe);

#endif