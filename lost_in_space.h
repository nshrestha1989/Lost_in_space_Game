#ifndef LOST_IN_SPACE_GAME_DATA
#define LOST_IN_SPACE_GAME_DATA
#include "splashkit.h"
#include <vector>
#include "power_up.h"
#include "player.h"
#include "villan.h"
using std::vector;

struct game_data
{
    player_data player;
    vector<power_up_data> power_ups;
    double timer = 2;
    villan_data villan;
    int game_state;
};

game_data new_game();
void draw_game(const game_data &game);
void update_game(game_data &game);
void add_power_up(game_data &game);
point_2d mini_map_cordinate_player(const player_data &player);

#endif