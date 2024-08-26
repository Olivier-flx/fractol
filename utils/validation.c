/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:01:35 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 18:51:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_strncmp(char *input, char *comp_text, int n)
{
	int	i;

	if (!input || !comp_text || n <= 0)
		return (0);
	i = 0;
	while (input[i] == comp_text[i] && i < n && input[i])
	{
		if (input[i] != comp_text[i])
			break ;
		i++;
	}
	return (input[i] - comp_text[i]);
}

void	putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || fd < 0)
		return ;
	i = 0;
	while (str[i])
	{
		if (write(fd, &str[i], 1) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}
