/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:15:33 by seblin            #+#    #+#             */
/*   Updated: 2024/01/23 09:40:21 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int 	get_line_length(t_point **pt_arr)
{
	int	len;
	
	len = 0;
	if (!*pt_arr)
		return (len);
	while (pt_arr[len] && !pt_arr[len]->line)	
		len++;
	return (++len);
}

int 	get_n_line(t_point **pt_arr)
{
	int	n;

	n = 0;
	if (!*pt_arr)
		return (n);
	while (*pt_arr)
		if ((*pt_arr++)->line == 1)
			n++;
	return (++n);
}
double	get_average(t_point **pt_arr, int axe)
{
	double	sum;
	int	i;

	i = -1;
	sum = 0.0;
	while (pt_arr[++i])	
		sum += pt_arr[i]->init_vect[axe];	
	if (i)	
		return (sum / i);
	return (0.0);
}

double	get_initial_scale(t_point **pt_arr)
{
	double 	scale;	
	double	coef;
	int		line_len;
	int		n_line;
	
	coef = 0.75;
	n_line = get_n_line(pt_arr);
	line_len = get_line_length(pt_arr);
	if (line_len > n_line)		
		scale = coef * WIDTH / line_len;
	else
		scale = coef * HEIGHT / n_line;
	return (scale);
}
