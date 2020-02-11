#include "cub3d.h"

int move_x(t_data *data, int value)
{
	int tmp;

	tmp = data->player.pos.x + value;
	// printf("H pos= [%d] [%d]\ttmp = %d \n", data->player.pos.x, data->player.pos.y, tmp%BLOCK_SIZE);
	if (tmp < (data->world.size.x * BLOCK_SIZE) &&	tmp > BLOCK_SIZE)
	{
		if (data->world.map[data->player.pos.y / BLOCK_SIZE][(tmp / BLOCK_SIZE)] != '1' && data->world.map[data->player.pos.y / BLOCK_SIZE][(tmp / BLOCK_SIZE)] != '3')
			data->player.pos.x = tmp;
		// else if (data->world.map[data->player.pos.y / BLOCK_SIZE][(tmp / BLOCK_SIZE)] == '2' && !((tmp%BLOCK_SIZE > BLOCK_SIZE/48) && (tmp%BLOCK_SIZE < BLOCK_SIZE - BLOCK_SIZE/48) && (data->player.pos.y%BLOCK_SIZE > BLOCK_SIZE/48) && (data->player.pos.y%BLOCK_SIZE < BLOCK_SIZE-BLOCK_SIZE/48)))
		// 	data->player.pos.x = tmp;
	}
	return (0);
}

int move_y(t_data *data, int value)
{
	int tmp;

	tmp = data->player.pos.y + value;
	// printf("Y pos= [%d] [%d]\ttmp = %d\n", data->player.pos.x, data->player.pos.y, tmp%BLOCK_SIZE);
	if (tmp < (data->world.size.y * BLOCK_SIZE) &&	tmp > BLOCK_SIZE)
	{
		if (data->world.map[tmp / BLOCK_SIZE][data->player.pos.x / BLOCK_SIZE] != '1' && data->world.map[tmp / BLOCK_SIZE][data->player.pos.x / BLOCK_SIZE] != '3')
			data->player.pos.y = tmp;
		// else if (data->world.map[tmp / BLOCK_SIZE][data->player.pos.x / BLOCK_SIZE] == '2' && !((tmp%BLOCK_SIZE >= BLOCK_SIZE/48) && (tmp%BLOCK_SIZE <= BLOCK_SIZE - BLOCK_SIZE/48) && (data->player.pos.x%BLOCK_SIZE > BLOCK_SIZE/48) && (data->player.pos.x%BLOCK_SIZE < BLOCK_SIZE-BLOCK_SIZE/48)))
		// 	data->player.pos.y = tmp;
	}
	return (0);
}

void	move(t_data *data, float direction)
{
	move_x(data, cosf(direction) * data->player.speed / 2); //REVIEW  NANI????? div par 2?
	move_y(data, sinf(direction) * -data->player.speed / 2);
}