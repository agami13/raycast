#include "header.h"

t_data	data;
int mapX = 8; 
int mapY = 8;
int mapS = 64;

char map[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

int	draw_map();
int	draw_player(t_palyer *player);
void	ft_put_pixel(t_data *data, int x, int y, int color);

// void	draw_laser(t_palyer *player)
// {

// }

int	key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_loop_end(data->mlx);
		free(data->player);
		return (0);
	}
	t_palyer *player = data->player;
	if (key == A) { player->pa -= 0.1; if (player->pa < 0) { player->pa += PI * 2;} player->delta_x = cos(player->pa) * 5; player->delta_y = sin(player->pa) * 5;} 
	if (key == D) { player->pa += 0.1; if (player->pa > PI * 2) { player->pa -= PI * 2;} player->delta_x = cos(player->pa) * 5; player->delta_y = sin(player->pa) * 5;}
	if (key == W) { player->xpos += player->delta_x; player->ypos += player->delta_y;}
	if (key == S) { player->xpos -= player->delta_x; player->ypos -= player->delta_y;}
	draw_map();
	draw_player(data->player);
	return (0);
}
int	draw_map()
{
    int outline_thickness = 1;

    for (int i = 0; i < mapY; i++)
    {
        for (int j = 0; j < mapX; j++)
        {
            int tile_x = j * mapS;
            int tile_y = i * mapS;

            if (map[i * mapX + j] == 1)
            {
                for (int y = 0; y < mapS; y++)
                {
                    for (int x = 0; x < mapS; x++)
                    {
                        ft_put_pixel(&data, tile_x + x, tile_y + y, 0x0000000);
                    }
                }

                for (int y = outline_thickness; y < mapS - outline_thickness; y++)
                {
                    for (int x = outline_thickness; x < mapS - outline_thickness; x++)
                    {
                        ft_put_pixel(&data, tile_x + x, tile_y + y, WHITE);
                    }
                }
            }
            else
            {
                for (int y = 0; y < mapS; y++)
                {
                    for (int x = 0; x < mapS; x++)
                    {
                        ft_put_pixel(&data, tile_x + x, tile_y + y, 0x00000000);
                    }
                }
                for (int y = outline_thickness; y < mapS - outline_thickness; y++)
                {
                    for (int x = outline_thickness; x < mapS - outline_thickness; x++)
                    {
                        ft_put_pixel(&data, tile_x + x, tile_y + y, 0xFF404040);
                    }
                }
            }
        }
    }
    return (0);
}
int draw_rotation_line(t_palyer *player)
{
    int thickness = 3;

    for (int i = 0; i < 10; i++) {
        int x = player->xpos + player->delta_x * i;
        int y = player->ypos + player->delta_y * i;
        for (int t = -thickness / 2; t <= thickness / 2; t++) {
            ft_put_pixel(&data, x + 5 + t, y + 5, GREEN); 
            ft_put_pixel(&data, x + 5, y + 5 + t, GREEN); 
        }
    }

    return 0;
}

int	draw_player(t_palyer *player)
{
    int thickness = 3;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			ft_put_pixel(&data, player->xpos + i, player->ypos + j, GREEN);
	}
	draw_rotation_line(player);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    return 0;
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*where_to_put = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)where_to_put = color;
}

int main()
{
	t_palyer *player = malloc(sizeof(t_palyer));
	data.player = player;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "boom");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	player->xpos = 64;
	player->ypos = 64;
	player->delta_x = cos(player->pa) * 5;
	player->delta_y = sin(player->pa) * 5;
	draw_map();
	draw_player(player);
	// mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);
}