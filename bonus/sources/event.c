/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:05:15 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 18:10:39 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"
#include "mlx.h"

double	get_initial_scale(t_point **pt_arr);

void	init_event(t_event *event, t_point **pt_arr)
{
	event->flag = 1;
	event->rx = 0.0;
	event->ry = 0.0;
	event->rz = 0.0;
	event->tx = 0.0;
	event->ty = 0.0;
	event->tz = -HEIGHT / 1.5;
	event->scl = get_initial_scale(pt_arr);
	event->scl_z = 1.0;
	event->scl_end = 1.0;
	event->persp = 0.0;
}
static void	key_press3(int keycode, t_event *event)
{
	if (keycode == 112)
		event->persp++;
	else if (keycode == 109)
		event->persp--;
	else if (keycode == 120)
		event->rx++;
	else if (keycode == 99)
		event->rx--;
	else if (keycode == 121)
		event->ry++;
	else if (keycode == 117)
		event->ry--;
	else if (keycode == 122)
		event->rz++;
	else if (keycode == 97)
		event->rz--;
}

static void	key_press2(int keycode, t_event *event)
{
	if (keycode == 65361)
		event->tx += 10;
	else if (keycode == 65363)
		event->tx -= 10;
	else if (keycode == 65362)
		event->ty += 10;
	else if (keycode == 65364)
		event->ty -= 10;
	else if (keycode == 65436)
		event->tz += 2;
	else if (keycode == 65438)
		event->tz -= 2;
}

int	key_press(int keycode, void *param[])
{
	t_event	*event;

	event = (t_event *) param[1];
	event->flag = 1;
	key_press2(keycode, event);
	key_press3(keycode, event);
	if (keycode == 102)
		event->scl_z += 0.1;
	else if (keycode == 103)
		event->scl_z -= 0.1;
	else if (keycode == 115)
		event->scl += 1;
	else if (keycode == 100)
		event->scl -= 1;	
	else if (keycode == 65432)
		event->scl_end += 0.1;
	else if (keycode == 65430)
		event->scl_end -= 0.1;
	else if (keycode == 114)
		init_event(event, (t_point **) param[0]);
	else if (keycode == 65307)
		mlx_loop_end(param[2]);
	return (0);
}
