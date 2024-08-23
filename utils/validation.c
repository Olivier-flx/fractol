/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:01:35 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/12 19:43:03 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_strncmp(char *input, char *comp_text, int n)
{
	int	i;

	if (!input || !comp_text || n <= 0)
		return (0);
	i = 0;
	while (input[i] == comp_text[i] && n > 0 && input[i])
	{
		if (input != comp_text)
			break ;
		i++;
		n--;
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

/*
void	valid_params_option(void char *str, int fd)
{
	char	**valid_arg;
	int		i;

	i = 0;
	//valid_arg[0] = "julia";
	//valid_arg[1] = "Mandelbrot";

	ft_printf("Use valid parameters such as : %s \n", valid_arg[i]);
	while (valid_arg[i])
		ft_printf("--> %s\n", valid_arg[i]);
	exit(0);
}
*/
