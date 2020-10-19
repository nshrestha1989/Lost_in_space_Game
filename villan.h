#ifndef LOST_IN_SPACE_VILLAN
#define LOST_IN_SPACE_VILLAN
#include "splashkit.h"
#include <vector>
#include "weapon.h"

struct villan_data
{
    sprite villan_sprite;
    vector<weapon_data> weapon;
};
villan_data new_villan();
void draw_villan(const villan_data &villan_to_draw);
void update_villan(villan_data &villan_to_update);
void villan_direction(villan_data & villan,int score);

#endif
