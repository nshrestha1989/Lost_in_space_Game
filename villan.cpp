#include "player.h"
#include "splashkit.h"
#include "power_up.h"
#include "villan.h"
#include "weapon.h"
#include "lost_in_space.h"


villan_data new_villan( )
{
    player_data player;
    villan_data villan;

    bitmap default_bitmap = bitmap_named("enemy");
    villan.villan_sprite = create_sprite(default_bitmap);

    sprite_set_x(villan.villan_sprite, 0);
    sprite_set_y(villan.villan_sprite, 400);

  
    
    return villan;
}

void draw_villan(const villan_data &villan_to_draw)
{
    draw_sprite(villan_to_draw.villan_sprite);
}
void update_villan(villan_data &villan_to_update)
{
    update_sprite(villan_to_update.villan_sprite);
}
void villan_direction(villan_data & villan, int score)
 {
         float dx = sprite_dx(villan.villan_sprite);
    float rotation = sprite_rotation(villan.villan_sprite);
   if (key_down(LEFT_KEY))
        sprite_set_rotation(villan.villan_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(villan.villan_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases

    if (key_typed(DOWN_KEY))
        sprite_set_dx(villan.villan_sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(villan.villan_sprite, dx + PLAYER_SPEED);

if((score>1 && score< 5) || (score > 6 && score < 8) || (score >10 && score < 15) || score > 20){
   if (key_typed(DOWN_KEY)){
        sprite_set_dx(villan.villan_sprite, dx - PLAYER_SPEED*1.5);
   }
    if (key_typed(UP_KEY)){
        sprite_set_dx(villan.villan_sprite, dx + PLAYER_SPEED*1.5);
    }
}

 }

 