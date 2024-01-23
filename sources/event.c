/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:05:15 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 22:23:24 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"
#include "mlx.h"

double	get_initial_scale(t_point **pt_arr);

void	init_event(t_event *event, t_point **pt_arr)
{
	event->flag = 1;
	event->rx = 25.0;
	event->ry = 0.0;
	event->rz = 45.0;
	event->tx = 0.0;
	event->ty = 0.0;
	event->tz = -HEIGHT / 1.5;
	event->scl = get_initial_scale(pt_arr);
	event->scl_z = 10.0;
	event->scl_end = 1.0;
	event->persp = 0.0;
}

int	key_press(int keycode, void *param[])
{
	t_event	*event;

	event = (t_event *) param[1];
	event->flag = 1;
	if (keycode == 65307)
		mlx_loop_end(param[2]);
	return (0);
}
