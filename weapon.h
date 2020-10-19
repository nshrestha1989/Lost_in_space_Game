
#ifndef LOST_IN_SPACE_WEAPON
#define LOST_IN_SPACE_WEAPON
#include "splashkit.h"


enum weapon_kind
{
    SATURN,
    ENEMYWEAPON,
    NOS,
    BATTERY,
    STAR,
    BULLET
};

struct weapon_data

{
    sprite weapon_sprite;
    weapon_kind kind_of_weapon;
};
void update_weapon(weapon_data &weapon_to_update);
void draw_weapon(const weapon_data &weapon_to_draw);

weapon_data weapon_up(double x, double y,int score,sprite player_sprite);
#endif