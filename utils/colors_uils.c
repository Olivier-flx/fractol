/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_uils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:13:11 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 21:13:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int interpolate_color(unsigned int start_color, unsigned int end_color, double t) {
	// Extraire les composantes RGB
	unsigned char start_r = (start_color >> 16) & 0xFF;
	unsigned char start_g = (start_color >> 8) & 0xFF;
	unsigned char start_b = start_color & 0xFF;

	unsigned char end_r = (end_color >> 16) & 0xFF;
	unsigned char end_g = (end_color >> 8) & 0xFF;
	unsigned char end_b = end_color & 0xFF;

	// Interpoler chaque composante
	unsigned char r = start_r + (unsigned char)((end_r - start_r) * t);
	unsigned char g = start_g + (unsigned char)((end_g - start_g) * t);
	unsigned char b = start_b + (unsigned char)((end_b - start_b) * t);

	// Recombiner les composantes en une seule couleur
	return ((r << 16) | (g << 8) | b);
}
