/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/06 12:43:13 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"

int	main(void)
{
	void	*mlx_connect;
	void	*mlx_window;
	
	mlx_connect = mlx_init();
	mlx_new_window(mlx_connect, 500, 500, "Alpha");
	mlx_loop(mlx_connect);
	return (0);
}