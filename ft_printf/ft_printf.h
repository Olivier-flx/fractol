/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:10:14 by ofilloux          #+#    #+#             */
/*   Updated: 2024/02/25 16:31:18 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>

int	ft_printf(char const *str, ...);
int	put_ptr(void *ptr);
int	put_digit(int digit);
int	put_integer(int integ);
int	put_unsigned_int(unsigned int u_int);
int	put_base16(unsigned int u_int, char *base, int control);

#endif
