#ifndef TREED_H
# define TREED_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <limits.h>
# include <string.h>

# define WIDTH 600
# define HEIGHT 600
# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2
# define RD 0.0174533
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define GREEN 0x0000FF00
# define WHITE 0xFFFFFFFF
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_player {
	float	xpos;
	float	ypos;
	float	delta_x;
	float	delta_y;
	float	pa;
}	t_palyer;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_palyer	*player;
}				t_data;

void	ft_put_pixel(t_data *data, int x, int y, int color);
int	draw_player(t_palyer *player);
int draw_rotation_line(t_palyer *player);
int	draw_map();
int	key_hook(int key, t_data *data);
void	draw_laser();

#endif
