/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 07:55:53 by svidot            #+#    #+#             */
/*   Updated: 2024/01/15 10:59:52 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

#define WIDTH 1000
#define HEIGHT 700
#define MTX 4
#define M_PI 3.14159265358979323846 // flag math ...

typedef struct s_point
{
	int	init_vect[MTX];
	int	*new_vect[MTX];
}	t_point;

#endif