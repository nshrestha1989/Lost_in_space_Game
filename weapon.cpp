#include "splashkit.h"
#include "power_up.h"
#include <vector>
#include "player.h"
#include "weapon.h"
#include "villan.h"
#include "lost_in_space.h"

/**
 * The power up map  function converts a power kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power you want the bitmap of
 * @return      The bitmap matching this power kind
 */
bitmap weapon_map(weapon_kind &kind)
{

    switch (kind)
    {
    case SATURN:
        return bitmap_named("saturn");
    case ENEMYWEAPON:
        return bitmap_named("enemyRock");
    case NOS:
        return bitmap_named("nos");
    case BATTERY:
        return bitmap_named("battery");
    case BULLET:
        return bitmap_named("bullet");
          default:
       return bitmap_named("star");
    }
}

weapon_data weapon_up(double x, double y,int score,sprite player_sprite)

{
    villan_data villan;
    weapon_data result;

    
    if (score > 0 and score <2 )
    {
        result.kind_of_weapon =SATURN;
      
    }
     else if (score > 2 and score <4)
    {
        result.kind_of_weapon = ENEMYWEAPON;
        
    }
    else if  (score > 4 and score <6)
    {
        result.kind_of_weapon =NOS;

    }
     else if (score > 6 and score <8)
    {
        result.kind_of_weapon = BATTERY;
    }
   else if   (score > 8 and score <10)
    {
        result.kind_of_weapon = BULLET;
    }
    else  
    {
        result.kind_of_weapon = STAR;
         
     }
    result.weapon_sprite = create_sprite(weapon_map(result.kind_of_weapon));

    sprite_set_x(result.weapon_sprite, x);
    sprite_set_y(result.weapon_sprite,y);
     sprite_set_dx(result.weapon_sprite, sprite_x(result.weapon_sprite)*0.01);
    sprite_set_dy(result.weapon_sprite,rnd(1,2) * 4 - 2);
    //sprite_set_heading(result.weapon_sprite,sprite_heading(player_sprite));
    // void sprite_move_to(sprite s, const point_2d &pt, float taking_seconds)
   
    //   sprite_move_to(result.weapon_sprite, center_point(player_sprite), 5);
//    move_sprite_to(result.weapon_sprite,sprite_x(player_sprite),sprite_y(player_sprite));
    return result;
}
void draw_weapon(const weapon_data &weapon_to_draw)
{
    draw_sprite(weapon_to_draw.weapon_sprite);
}

void update_weapon(weapon_data &weapon_to_update)
{

    update_sprite(weapon_to_update.weapon_sprite);
}
