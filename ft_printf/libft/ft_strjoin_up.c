/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:52:14 by marvin            #+#    #+#             */
/*   Updated: 2024/02/18 19:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	free_str(char *s1, char *s2, int s1_free, int s2_free)
{
	if (s1_free)
		free(s1);
	if (s2_free)
		free(s2);
}

char	*ft_strjoin_up(char *s1, char *s2, int s1_free, int s2_free)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;

	if (!s1)
		if (s2)
			return (s2);
	if (!s2)
	{
		if (s1)
			return (s1);
		else
			return (NULL);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = (char *) malloc(sizeof (char) * (s1_len + s2_len + 1));
	if (!s3)
		return (NULL);
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;
	*s3 = '\0';
	return (free_str(s1, s2, s1_free, s2_free), (s3 - s2_len - s1_len));
}
