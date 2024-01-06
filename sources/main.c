/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/06 20:40:40 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	main(void)
{
	void	*mlx_connect;
	void	*mlx_window;
	
	mlx_connect = mlx_init();
	mlx_new_window(mlx_connect, 500, 500, "Alpha");
	mlx_loop(mlx_connect);
	(void) mlx_window;
	return (0);
}