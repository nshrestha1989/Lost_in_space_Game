
#include "splashkit.h"
#include "power_up.h"
#include <vector>
#include "player.h"

/**
 * The power up map  function converts a power kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power you want the bitmap of
 * @return      The bitmap matching this power kind
 */
bitmap power_up_map(power_up_kind &kind)
{

    switch (kind)
    {
    case SHIELD:
        return bitmap_named("shield");
    case POWER:
        return bitmap_named("power");
    case POTION:
        return bitmap_named("potion");
    case FUEL:
        return bitmap_named("fuel");
    case DROPS:
        return bitmap_named("drops");
    case HEALTH:
        return bitmap_named("heart");
    default:
        return bitmap_named("diamond");
    }
}
power_up_data new_power_up(double x, double y, double timer)

{

    power_up_data result;
    //randomly pick a power up kind
    if ((timer >0.10 and timer<0.30) or
     (timer >0.7 and timer<0.8) or (timer > 1.1 and timer<1.2 )){
        result.kind = HEALTH;
     }
     else
     {
        result.kind = static_cast<power_up_kind>(rnd(6));
     }
     
  
    //create the sprite by pickin random kind from  power_up_map function
    result.power_up_sprite = create_sprite(power_up_map(result.kind));
    //result.kind= random_kind;
    //positioning the power up bitmap at location x and  y
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    sprite_set_dx(result.power_up_sprite, 0);
   sprite_set_dy(result.power_up_sprite, rnd(1,3) * 4 - 2);
   // sprite_set_dx(result.power_up_sprite, rnd());
    //sprite_set_dy(result.power_up_sprite, rnd());
    //sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    //sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);

    return result;
}
void draw_power_up(const power_up_data &power_to_draw)
{
    draw_sprite(power_to_draw.power_up_sprite);
}

void update_power_up(power_up_data &power_to_update)
{

    update_sprite(power_to_update.power_up_sprite);
}
