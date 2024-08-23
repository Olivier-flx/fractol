COMPIL = cc -Wall -Wextra -Werror

NAME = libftprintf.a

SRC = ft_printf.c\
	put_base_16.c\
	put_numb.c\
	put_ptr.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

${NAME}: $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c ft_printf.h Makefile
	$(COMPIL) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
