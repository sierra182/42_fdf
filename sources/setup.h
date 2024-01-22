/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 07:55:53 by svidot            #+#    #+#             */
/*   Updated: 2024/01/22 10:21:10 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

#define WIDTH 1400
#define HEIGHT 787
#define MTX 4
#define M_PI 3.14159265358979323846 // flag math ...

typedef struct s_point
{
	double	init_vect[MTX];
	double	new_vect[MTX];
	int		line;
}	t_point;

#endif