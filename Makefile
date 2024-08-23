# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/11 21:56:26 by ofilloux          #+#    #+#              #
#    Updated: 2024/08/23 12:14:23 by ofilloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
COMP = cc
CFLAGS = -Wall -Werror -Wextra -g

INCLUD_DIR = ./inc
FT_PRINTF_DIR = inc/ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
MLX_DIR = inc/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_linux.a

UTILS = ./utils/handle_errors.c \
		./utils/validation.c \
		./utils/cmd.c \
		./utils/mgmt_def_zoom.c \
		./utils/math.c \
		./fract_run/create_run_f.c \
		./fract_run/fract_render.c

SRC = $(UTILS) \
	./main.c

INCLUDE = ./inc/fractol.h\
		./inc/colors.h

OBJ = $(SRC:.c=.o)


######################

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_LIB) $(MLX_LIB)
	$(COMP) $(CFLAGS) $(OBJ) -L$(FT_PRINTF_DIR) -L$(MLX_DIR) -lftprintf -lmlx -lXext -lX11 -lm -lz -O3 -o $(NAME)

$(FT_PRINTF_LIB):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c $(INCLUDE) Makefile
	$(COMP) $(CFLAGS) -I$(INCLUD_DIR) -I$(FT_PRINTF_DIR) -I$(MLX_DIR) -O3 -c $< -o $@
## utiliser -03 pour un niveau d'optimisation de la compil plus élevé
## pas besoin de compiler explicitement votre fichier d'en-tête (header.h), $(INCLUDE)
##### $< : Variable automatique qui représente le premier prérequis de la règle en cours. $< représente le fichier source (.c) qui est en cours de compilation.
##### -c : Cela indique au compilateur de ne générer que le fichier objet (.o) à partir du fichier source donné
##### -o : Spécifier le nom du fichier de sortie généré
##### $@ : représente le nom de la cible en cours de construction, c'est-à-dire le fichier objet (.o)

####### rm -f  = nettoyer les anciens fichiers binaires avant de générer de nouveaux fichiers.
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
