/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drow_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 11:27:07 by widraugr          #+#    #+#             */
/*   Updated: 2020/01/30 11:41:46 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	init_ch(t_ch *ch)
{
	ch->bits_adr = 4;
	ch->size_adr = WIDTH;
	ch->endian = 0;
	ch->op = NULL;
	ch->mlx = mlx_init();
	ch->window = mlx_new_window(ch->mlx, WIDTH, HEIGHT, "Push swap");
	ch->img_ptr = mlx_new_image(ch->mlx, WIDTH, HEIGHT);
	ch->data_adr = mlx_get_data_addr(ch->img_ptr,
			&ch->bits_adr, &ch->size_adr, &ch->endian);
}

void	check(char *line)
{
	if (ft_strlen(line) > 4 || ft_strlen(line) < 2)
	{
		ft_printf("Operation \"%s\" is not valid.\n", line);
		exit(0);
	}
	if (ft_strstr(STROP, line) == NULL)
	{
		ft_printf("Operation \"%s\" is not valid.\n", line);
		exit(0);
	}
}

t_coor	ft_draw_line_source(t_coor *delta,
		t_coor *sign, t_coor point1, t_coor point2)
{
	(*delta).x = ABS((point2.x - point1.x));
	(*delta).y = ABS((point2.y - point1.y));
	(*sign).x = (point1.x < point2.x) ? 1 : -1;
	(*sign).y = (point1.y < point2.y) ? 1 : -1;
	return (point1);
}

void	put_pixel_adr(t_ch *ch, t_coor point)
{
	int i;

	if (point.x >= WIDTH || point.y >= HEIGHT || point.x <= 0 || point.y <= 0)
		return ;
	i = (point.x * ch->bits_adr / 8) + (point.y * ch->size_adr);
	ch->data_adr[i] = point.color;
	ch->data_adr[++i] = point.color >> 8;
	ch->data_adr[++i] = point.color >> 16;
	ch->data_adr[++i] = 0;
}

void	ft_draw_line(t_ch *ch, t_coor point1, t_coor point2, int color)
{
	t_coor	delta;
	t_coor	sign;
	t_coor	point;
	int		error;
	int		error2;

	point = ft_draw_line_source(&delta, &sign, point1, point2);
	error = delta.x - delta.y;
	put_pixel_adr(ch, point2);
	while (point.x != point2.x || point.y != point2.y)
	{
		put_pixel_adr(ch, point);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			point.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			point.y += sign.y;
		}
		point.color = color;
	}
}
