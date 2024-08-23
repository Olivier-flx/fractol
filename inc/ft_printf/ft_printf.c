/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:33:41 by ofilloux          #+#    #+#             */
/*   Updated: 2024/02/25 15:45:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	put_ptr(void *ptr);
int	put_digit(int digit);
int	put_integer(int integ);
int	put_unsigned_int(unsigned int u_int);
int	put_base16(unsigned int u_int, char *base, int control);
int	put_ptr(void *ptr);

int	put_string(char *str_arg)
{
	int	i;

	i = 0;
	if (!str_arg)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		else
			return (6);
	}
	while (str_arg[i])
	{
		if (write(1, &str_arg[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	put_c(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	check_c(char const c, va_list args)
{
	int	ret_len;

	ret_len = 0;
	if (c == '%')
		ret_len = write(1, &c, 1);
	else if (c == 'c')
		ret_len = put_c(va_arg(args, int));
	else if (c == 's')
		ret_len = put_string(va_arg(args, char *));
	else if (c == 'p')
		ret_len = put_ptr(va_arg(args, void *));
	else if (c == 'i' || c == 'd')
		ret_len = put_integer(va_arg(args, int));
	else if (c == 'u')
		ret_len = put_unsigned_int(va_arg(args, unsigned int));
	else if (c == 'x')
		ret_len = put_base16(va_arg(args, unsigned int), "0123456789abcdef", 0);
	else if (c == 'X')
		ret_len = put_base16(va_arg(args, unsigned int), "0123456789ABCDEF", 0);
	else
		return (-1);
	if (ret_len == -1)
		return (-1);
	return (ret_len);
}

int	control_args(va_list args, int	*i, const char *str)
{
	int	control;
	int	tot_len;

	tot_len = 0;
	if (str[*i] == '%')
	{
		(*i)++;
		control = check_c(str[*i], args);
		if (control == -1)
			return (-1);
		tot_len = control;
	}
	else
	{
		if (write(1, &str[*i], 1) == -1)
			return (-1);
		tot_len++;
	}
	return (tot_len);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		tot_len;
	int		i;
	int		control;

	i = -1;
	tot_len = 0;
	va_start(args, str);
	while (str[++i])
	{
		control = control_args(args, &i, str);
		if (control == -1)
			return (-1);
		else
			tot_len += control;
	}
	va_end(args);
	return (tot_len);
}

/*`
int main () 
{
	int ret;

	ret = ft_printf("\001\002\007\v\010\f\r\n");
	printf("\n return value : %i\n\n", ret);

	int ret2;
	ret2 = printf("\001\002\007\v\010\f\r\n");
	printf("\n return value : %i\n\n", ret2);

	void *pointer;
	pointer = 0;
	int ret3;
	ret3 = ft_printf("%p\n", pointer);
	printf("return value : %i\n\n", ret3);

	int ret31 = printf("%p", pointer);
	printf("return value : %i\n\n", ret31);

}

*/
