/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:03:59 by mavitori          #+#    #+#             */
/*   Updated: 2024/02/19 16:14:19 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_hook(void *param)
{
	t_fractol	*fractol;
	mlx_t		*mlx;
	double		factor;

	fractol = (t_fractol *)param;
	mlx = (*fractol).mlx;
	factor = 0.04 * (*fractol).zoom_range;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		(*fractol).move_y -= factor;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		(*fractol).move_y += factor;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		(*fractol).move_x -= factor;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		(*fractol).move_x += factor;
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
		ft_zoom_in(fractol);
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_RIGHT))
		ft_zoom_out(fractol);
	if (mlx_is_key_down(mlx, MLX_KEY_ENTER))
		ft_color_shift(fractol);
}

void	ft_zoom_in(t_fractol *fractol)
{
	double	zoom_before;
	double	mouse_x;
	double	mouse_y;

	zoom_before = (*fractol).zoom_range;
	(*fractol).zoom_range -= (0.1 * zoom_before);
	mlx_get_mouse_pos(fractol->mlx, &fractol->mouse_x, &fractol->mouse_y);
	mouse_x = ((double)(fractol->mouse_x) / fractol->width - 0.25) * 2.0;
	mouse_y = ((double)(fractol->mouse_y) / fractol->height - 0.25) * 2.0;
	(*fractol).move_x += (mouse_x * 0.1 * zoom_before);
	(*fractol).move_y += (mouse_y * 0.1 * zoom_before);
}

void	ft_zoom_out(t_fractol *fractol)
{
	double	zoom_before;
	double	mouse_x;
	double	mouse_y;

	zoom_before = (*fractol).zoom_range;
	(*fractol).zoom_range += (0.1 * zoom_before);
	mlx_get_mouse_pos(fractol->mlx, &fractol->mouse_x, &fractol->mouse_y);
	mouse_x = ((double)(fractol->mouse_x) / fractol->width - 0.25) * 2.0;
	mouse_y = ((double)(fractol->mouse_y) / fractol->height - 0.25) * 2.0;
	(*fractol).move_x -= (mouse_x * 0.1 * zoom_before);
	(*fractol).move_y -= (mouse_y * 0.1 * zoom_before);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (ydelta > 0)
		ft_zoom_in(fractol);
	else if (ydelta < 0)
		ft_zoom_out(fractol);
	if (xdelta < 0)
		ft_zoom_in(fractol);
	else if (xdelta > 0)
		ft_zoom_out(fractol);
}
