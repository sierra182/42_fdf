/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:40:02 by svidot            #+#    #+#             */
/*   Updated: 2024/01/07 10:11:58 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include "mlx.h"

void	input_handle(char *argv[])
{
	int	fd;
	
	fd = open(*(argv + 1), O_RDONLY);
	if (fd < 0)
		return (perror(*(argv + 1)), exit(1));
}

int	main(int argc, char *argv[])
{
	void	*mlx_connect;
	void	*mlx_window;
	
	if (argc != 2)
		return (1);
	input_handle();  // fd
	mlx_connect = mlx_init(); // mlx
	mlx_new_window(mlx_connect, 500, 500, "Alpha");
	mlx_loop(mlx_connect);		
	return (0);
}