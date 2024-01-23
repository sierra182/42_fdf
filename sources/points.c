void	save_new_vect(t_point **pt_arr)
{	
	int	i;

	while (*pt_arr)
	{
		i = -1;
		while (++i < MTX - 1)
			(*pt_arr)->init_vect[i] = (*pt_arr)->new_vect[i];	
		pt_arr++;
	}
}
t_point **copy_points(t_point **pt_arr)
{
	t_point **copy;
	int		i;
	int		j;

	i = 0;
	while (pt_arr[i])	
		i++;	
	copy = (t_point **) ft_calloc(i + 1, sizeof(t_point *));
	i = 0;
	while (pt_arr[i])
	{
		copy[i] = malloc(sizeof(t_point));	
		copy[i]->init_vect[3] =  1 ;
		j = -1;
		while (++j < MTX)		
			copy[i]->new_vect[j] = pt_arr[i]->new_vect[j];
		copy[i]->line = pt_arr[i]->line;
		i++;		
	}
	return (copy);
}

void	homogenize_pt_arr(t_point **pt_arr)
{
	int	i;

	while (*pt_arr)
	{
		i = 0;
		if ((*pt_arr)->new_vect[MTX - 1]) 
			while (i < 2)			
				(*pt_arr)->new_vect[i++] /= (*pt_arr)->new_vect[MTX - 1];
		pt_arr++;
	}
}