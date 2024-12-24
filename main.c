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

float dist(float ax, float ay, float bx, float by)
{
    return sqrt(pow(bx - ax, 2) + pow(by - ay, 2));
}


void draw_line(float xpos, float ypos, float rx, float ry, int color)
{
    float dx = rx - xpos;
    float dy = ry - ypos;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = xpos;
    float y = ypos;
    for (int i = 0; i <= steps; i++) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            ft_put_pixel(&data, (int)x, (int)y, color);
        }
        x += x_inc;
        y += y_inc;
    }
}

void draw_3D(float disT, int r)
{
    int screen_width = 300;   // Width of the rendering window
    int screen_height = 300; // Height of the rendering window
    int x_offset = 512 + 650; // Offset for placing the rendered map next to the 2D map

    int wall_color = RED;
    int ceiling_color = 0x87CEEB; // Sky blue for ceiling
    int floor_color = 0x8B4513;   // Brown for floor

    // Render the map with the offset
    float lineH = (mapS * screen_height) / disT; // Calculate line height relative to the screen
    if (lineH > screen_height) { 
        lineH = screen_height;  // Cap it to screen height
    }

    int lineO = (screen_height / 2) - (lineH / 2); // Top of the wall
    int lineEnd = (screen_height / 2) + (lineH / 2); // Bottom of the wall

    // Draw the ceiling
    for (int y = 0; y < lineO; y++) {
        ft_put_pixel(&data, r + x_offset, y, ceiling_color); // Apply x_offset
    }

    // Draw the wall
    for (int y = lineO; y < lineEnd; y++) {
        ft_put_pixel(&data, r + x_offset, y, wall_color); // Apply x_offset
    }

    // Draw the floor
    for (int y = lineEnd; y < screen_height; y++) {
        ft_put_pixel(&data, r + x_offset, y, floor_color); // Apply x_offset
    }
}





void	draw_laser()
{
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;
    t_palyer *player = data.player;

    ra = player->pa - (RD * 30);
    if (ra < 0) { ra += 2 * PI;}
    if (ra > 2*PI) { ra -= 2 * PI;}
    for (r = 0; r < 60; r++) {
        dof = 0;
        float disH = 1000000, hx = player->xpos, hy = player->ypos;
        float aTan;
        if (ra == 0 || ra == PI) {
            aTan = 0;
        } else {
            aTan = -1 / tan(ra);
        }
        if (ra > PI) { 
            ry = ((int)player->ypos / 64) * 64 - 1;
            rx = (player->ypos - ry) * aTan + player->xpos;
            yo = -64;
            xo = -yo * aTan;
        } else if (ra < PI) {
            ry = ((int)player->ypos / 64) * 64 + 64;
            rx = (player->ypos - ry) * aTan + player->xpos;
            yo = 64;
            xo = -yo * aTan;
        } else {
            rx = player->xpos;
            ry = player->ypos;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            if (mx < 0 || mx >= mapX || my < 0 || my >= mapY) {
                hx = rx; hy = ry; disH = dist(player->xpos, player->ypos, hx, hy);
                dof = 8;
                break;
            }
            mp = my * mapX + mx;
            if (map[mp] == 1) {
                hx = rx;
                hy = ry;
                disH = dist(player->xpos, player->ypos, hx, hy);
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

//////////////////////////// vertical lines ////////////////////////////////////

        dof = 0;
        float disV = 1000000, vx = player->xpos, vy = player->ypos;
        float nTan;
        if (ra == 0 || ra == PI) {
            nTan = 0;
        } else {
            nTan = -tan(ra);
        }
        if (ra > PI2 && ra < PI3) { 
            rx = ((int)player->xpos / 64) * 64 - 1;
            ry = (player->ypos - rx) * nTan + player->ypos;
            xo = -64;
            yo = -xo * nTan;
        } else if (ra < PI2 || ra > PI3) {
            rx = ((int)player->xpos / 64) * 64 + 64;
            ry = (player->xpos - rx) * nTan + player->ypos;
            xo = 64;
            yo = -xo * nTan;
        } else {
            rx = player->xpos;
            ry = player->ypos;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            if (mx < 0 || mx >= mapX || my < 0 || my >= mapY) {
                dof = 8;
                break;
            }
            mp = my * mapX + mx;
            if (map[mp] == 1) {
                vx = rx;
                vy = ry;
                disV = dist(player->xpos, player->ypos, vx, vy);
                dof = 8;
            } else {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        if (disV < disH) { rx = vx; ry = vy; disT = disV;}
        if (disH < disV) { rx = hx; ry = hy; disT = disH;}
        draw_line(player->xpos + 5, player->ypos + 5, rx, ry, GREY);
        // ---- 3D start ---- //
        draw_3D(disT, r);
        ra += RD;
        if (ra < 0) { ra += 2 * PI;}
        if (ra > 2*PI) { ra -= 2 * PI;}
    }
}

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
    draw_laser();
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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			ft_put_pixel(&data, player->xpos + i, player->ypos + j, GREEN);
	}
	// draw_rotation_line(player);
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
	data.win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "boom");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
    player->xpos = 72;
	player->ypos = 72;
	player->delta_x = cos(player->pa) * 5;
	player->delta_y = sin(player->pa) * 5;
	draw_map();
	draw_player(player);
	// mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx);
    return 0;
}