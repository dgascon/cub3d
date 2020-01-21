#include "cub3d.h"

int move_up(t_data *data)
{
    t_coord val_default;

    val_default.x = data->player.pos.x;
    val_default.y = data->player.pos.y;
    data->player.pos.x += cos(data->player.pov) * data->player.speed; 
	data->player.pos.y -= sin(data->player.pov) * data->player.speed; //deplacement 
    if (data->world.map[data->player.pos.y / BLOCK_SIZE][data->player.pos.x / BLOCK_SIZE] == '1' 
    || (data->player.pos.y) > (data->world.size.y * BLOCK_SIZE) - 1
    || (data->player.pos.x) > (data->world.size.x * BLOCK_SIZE) - 1
    || (data->player.pos.y) < 1
    || (data->player.pos.x) < 1)
    {
        data->player.pos.x = val_default.x; 
        data->player.pos.y = val_default.y; //deplacement 
        return (0);
    }
    return (1);
}

int move_down(t_data *data)
{
    t_coord val_default;

    val_default.x = data->player.pos.x;
    val_default.y = data->player.pos.y;
    data->player.pos.x -= cos(data->player.pov) * data->player.speed; 
	data->player.pos.y += sin(data->player.pov) * data->player.speed; //deplacement 
    if (data->world.map[data->player.pos.y / BLOCK_SIZE][data->player.pos.x / BLOCK_SIZE] == '1'
    || (data->player.pos.y) > (data->world.size.y * BLOCK_SIZE) - 1 
    || (data->player.pos.x) > (data->world.size.x * BLOCK_SIZE) - 1
    || (data->player.pos.y) < 1
    || (data->player.pos.x) < 1)
    {
        data->player.pos.x = val_default.x; 
        data->player.pos.y = val_default.y;
        return (0);
    }
    return (1);
}
