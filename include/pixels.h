/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:22:17 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 12:23:34 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

#include "setup.h"
#include "mlx.h"
#include <unistd.h>

void	draw_line(double *vct, double *vct_prm);
int 	get_line_length(t_point **pt_arr);

#endif