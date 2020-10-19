
#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"
#include "villan.h"
#include "weapon.h"
#define rangeStart -1500
#define rangeend 1500

game_data new_game()
{
    game_data result;
    result.player = new_player();

    result.villan = new_villan();

    return result;
}
void add_power_up(game_data &game)
{
    game.power_ups.push_back(new_power_up(rnd(rangeStart, rangeend), rnd(rangeStart, rangeend), game.timer));
}
void add_weapon_attack(game_data &game)
{
    if (rnd() < 0.05)
    {
        game.villan.weapon.push_back(weapon_up(sprite_x(game.villan.villan_sprite), sprite_y(game.villan.villan_sprite), game.player.score, game.player.player_sprite));
    }
}
void apply_power_up(game_data &game, power_up_kind kind)
{
    load_sound_effect("sound1", "sound.wav");
    play_sound_effect("sound1");
    game.player.fuel_pct = game.player.fuel_pct + 0.25;
    game.timer = game.timer + 0.125;
    if (game.timer > 2)
    {
        game.timer = 2;
    }
    
    game.player.score = game.player.score + 1;

    if (game.player.fuel_pct > 1)
    {
        game.player.fuel_pct = 1;
    }

    if (kind == DIAMOND)
    {
        write_line("DIAMOND: " + to_string(kind));
        game.player.diamond_count++;
    }
    else if (kind == SHIELD)
    {
        write_line("SHIELD " + to_string(kind));
        game.player.shield_count++;
    }
    else if (kind == HEALTH)
    {
        write_line("HEALTH " + to_string(kind));
        game.player.health_pct += 0.25;
    }
    if (game.player.health_pct > 1)
    {
        game.player.health_pct = 1;
    }
}
void remove_power_up(game_data &game, int index)
{

    game.power_ups.erase(game.power_ups.begin() + index);
}
void remove_weapon_icon(game_data &game, int index)
{
    game.villan.weapon.erase(game.villan.weapon.begin() + index);
}
void apply_injury(game_data &game, weapon_kind kind)
{
    load_sound_effect("sound1", "sound.wav");
    play_sound_effect("sound1");
    switch (kind)
    {
    case SATURN:
        game.player.diamond_count--;
        game.player.health_pct = game.player.health_pct - 0.0125;
        break;
    case STAR:
        game.player.shield_count--;
        game.player.health_pct = game.player.health_pct - 0.0125;
        break;
    case ENEMYWEAPON:
        game.player.score--;
        game.player.health_pct = game.player.health_pct - 0.0125;
        break;
    case BULLET:
        game.player.health_pct = game.player.health_pct - 0.125;
        break;
    case BATTERY:
        game.player.health_pct = game.player.health_pct - 0.125;
        break;
    default:
        game.player.score--;
        game.player.shield_count--;
        game.player.diamond_count--;
        break;
    }
}

void check_collision_with_villan(game_data &game)
{
    vector<int> remove_weapon_index;
    int index1;

    for (index1 = game.villan.weapon.size() - 1; index1 >= 0; index1--)
    {
        if (sprite_collision(game.player.player_sprite, game.villan.weapon[index1].weapon_sprite))
        {
            remove_weapon_index.push_back(index1);
            apply_injury(game, game.villan.weapon[index1].kind_of_weapon);
        }
    }
    for (int i = 0; i < remove_weapon_index.size(); i++)
    {
        remove_weapon_icon(game, remove_weapon_index[i]);
    }
}
void check_collision(game_data &game)
{
    vector<int> remove_powerup_index;
    int index;

    for (index = game.power_ups.size() - 1; index >= 0; index--)
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[index].power_up_sprite))
        {
            remove_powerup_index.push_back(index);
            apply_power_up(game, game.power_ups[index].kind);
        }
    }

    for (int i = 0; i < remove_powerup_index.size(); i++)
    {
        // remove_power_up(game, index);
        remove_power_up(game, remove_powerup_index[i]);
    }
}
void update_game(game_data &game)
{
    update_player(game.player);
    update_villan(game.villan);
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        update_power_up(game.power_ups[i]);
    }
    check_collision(game);
    if (rnd() < 0.05)
    {
        add_power_up(game);
    }
    if (game.player.shield_count < 0)
    {
        game.player.shield_count = 0;
    }
    if (game.player.diamond_count < 0)
    {
        game.player.diamond_count = 0;
    }

    game.timer = game.timer - 2 * 0.000278;

    if (game.timer <= 0)
    {
        game.timer = 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < game.villan.weapon.size(); i++)
    {
        update_weapon(game.villan.weapon[i]);
    }
    check_collision_with_villan(game);
    add_weapon_attack(game);
    villan_direction(game.villan, game.player.score);

    //////////////////////////////////////////////////////////
}

point_2d mini_map_cordinate_player(const player_data &player)
{
    double X = (sprite_x(player.player_sprite) - (-1500)) / 3000 * 100 + 1050;
    double Y = (sprite_y(player.player_sprite) - (-1500)) / 3000 * 100 + 25;

    return point_at(X, Y);
}
point_2d mini_map_cordinate(const power_up_data &power_up)
{
    double X = (sprite_x(power_up.power_up_sprite) - (-1500)) / 3000 * 100 + 1050;
    double Y = (sprite_y(power_up.power_up_sprite) - (-1500)) / 3000 * 100 + 25;

    return point_at(X, Y);
}
void draw_mini_map(const game_data &game)
{

    for (int i = 0; i < game.power_ups.size(); i++)
    {
        point_2d mini_map = mini_map_cordinate(game.power_ups[i]);

        write_line(mini_map.x);
        write_line(mini_map.y);
        if (mini_map.y <= 125 and mini_map.y >= 25 and mini_map.x <= 1150 and mini_map.x >= 1050)
        {
            draw_pixel(COLOR_WHITE, mini_map_cordinate(game.power_ups[i]), option_to_screen());
        }
    }
    draw_pixel(COLOR_RED, mini_map_cordinate_player(game.player), option_to_screen());
}

void draw_hud(const game_data &game)
{

    clear_screen(COLOR_BLACK);
     draw_bitmap("spacebackground", 0, 0, option_to_screen());
    
    fill_rectangle(COLOR_GRAY, 0, 0, 1200, 150, option_to_screen());
    fill_rectangle(COLOR_BLACK, 1050, 25, 100, 100, option_to_screen());
  
    fill_rectangle(COLOR_BLACK, 1050, 25, 100, 100, option_to_screen());
    draw_text("SCORE: " + to_string(game.player.score), COLOR_BLACK, 0, 70, option_to_screen());
    draw_text("TIMER 2 Min : " + to_string(game.timer * 60), COLOR_BLACK, 0, 120, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, 0, 90, option_to_screen());
    // draw image shield after the image full by taking width of full image as x and y as 0
    draw_bitmap("shield", bitmap_width("full"), 0, option_to_screen());
    // draw text of shield count in the location of after the width(y) of full image and shield imange and in the middle of shield as y
    draw_text(" = " + to_string(game.player.shield_count), COLOR_BLACK, bitmap_width("shield") + bitmap_width("full"), bitmap_height("shield") / 2, option_to_screen());
    //draw diamond imange
    draw_bitmap("diamond", 600, 0, option_to_screen());
    //draw text of dimond count at the center after diamond image and in the middle height
    draw_text(" = " + to_string(game.player.diamond_count), COLOR_BLACK, 600 + bitmap_width("diamond"), bitmap_height("diamond") / 2, option_to_screen());
    //draw the imange red bar for empty indication
    draw_bitmap("red_bar", 0, 0, option_to_screen());
    // draw image full for the level of fuel gauge
    draw_bitmap("full", 0, 0, option_part_bmp(0, 0, (game.player.fuel_pct ) * bitmap_width("full"), bitmap_height("full"), option_to_screen()));
      draw_text("FUEL %: " + to_string(game.player.fuel_pct * 100), COLOR_BLACK, 0, 50, option_to_screen());
    draw_mini_map(game);
    if (game.timer == 0 || game.player.score < 0 || game.player.health_pct == 0 || game.player.fuel_pct == 0)
    {
        draw_bitmap("GameOver", 400, 400, option_to_screen());
    }
    draw_text("Health Status:  " + to_string(game.player.health_pct * 100), COLOR_BLACK, 0, 140, option_to_screen());
 



}

void draw_game(const game_data &game)
{

    draw_hud(game);
    draw_player(game.player);
    draw_villan(game.villan);

    for (int i = 0; i < game.power_ups.size(); i++)
    {

        draw_power_up(game.power_ups[i]);
    }
    for (int i = 0; i < game.villan.weapon.size(); i++)
    {

        draw_weapon(game.villan.weapon[i]);
    }

}