# include "header.h"

// void	draw_laser(t_data *data)
// {
// 	int r, mx, my, mp, dof;
// 	float rx, ry, ra, xo, yo;
// 	t_palyer *player = data->player;

// 	ra = data->player->pa;
// 	for (r == 0; r < 1; r++)
// 	{
// 		dof = 0;
// 		float aTan = -1/tan(ra);
// 		if (ra > PI) { ry = (((int)player->ypos >> 6) << 6) - 0.0001; rx = (player->ypos - ry) * aTan + player->xpos; yo = -64; xo=-yo * aTan; }
// 		if (ra < PI) { ry = (((int)player->ypos >> 6) << 6) + 64; rx = (player->ypos - ry) * aTan + player->xpos; yo = 64; xo=-yo * aTan; }
// 		if (ra == 0 || ra == PI) {rx = player->xpos; ry = player->ypos; dof = 8;}
// 		while (dof < 8)
// 		{
// 			mx = (int)rx >> 6; my = (int)(ry)>> 6; mp = my * mapX + mx;
// 			if (mp < mapX * mapY && map[mp] == 1) { dof = 8; }
// 			else { rx += xo; ry += yo; dof += 1; } 
// 		}
// 		for (int i = 0; i < ry; i++)
// 		{
// 			for (int j = 0; j < rx; j++)
// 				ft_put_pixel(data, j, i, GREEN);
// 		}
// 	}
// }
