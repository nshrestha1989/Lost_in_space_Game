#ifndef LOST_IN_SPACE_POWER
#define LOST_IN_SPACE_POWER

#include "splashkit.h"
#include "splashkit.h"
#include <vector>
#include "power_up.h"

using namespace std;

/**
 * Different options for the kind of power.
 * Adjusts the image used.
 */

enum power_up_kind
{
    SHIELD,
    POWER,
    POTION,
    FUEL,
    DROPS,
    DIAMOND,
      HEALTH

};
/**
 * The power up data keeps track of all of the information related to the power.
 * 
 * @field   power_up_sprite   The power's sprite - used to track different power
 * @field   kind            Current power kind
 */
struct power_up_data
{
    sprite power_up_sprite;
    power_up_kind kind;
};

bitmap power_up_map(power_up_kind &kind);
/**s
 * Creates a power kind in the position x and y.
 * 
 * @returns     The new power data
 */
power_up_data new_power_up(double x, double y, double timer);
/**
 * update of the power - .
 * 
 * @param power_to_update      The power kind being updated
 */

void update_power_up(power_up_data &power_to_update);
/**
 * Draws the power kind on the screen. 
 * 
 * @param power_to_draw    The power kind to draw to the screen
 */
void draw_power_up(const power_up_data &power_to_draw);

#endif