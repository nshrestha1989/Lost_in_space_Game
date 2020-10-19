
#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"
game_data game;
/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */

void start_menu(game_data &game)
{
    clear_screen();
    load_font("font", "Halo.ttf");
    load_font("sofachrome", "sofachrome.ttf");
    load_font("BIONICKIDSIMPLE", "BIONICKIDSIMPLE.ttf");

    draw_bitmap("welcome", 0, 0, option_to_screen());
    draw_text("WELCOME  ", COLOR_ORANGE, "BIONICKIDSIMPLE", 70, 200, 20, option_to_screen());
    draw_text("TO ", COLOR_ORANGE, "BIONICKIDSIMPLE", 70, 450, 100, option_to_screen());
    draw_text("LOST IN SPACE ", COLOR_ORANGE, "BIONICKIDSIMPLE", 70, 0, 180, option_to_screen());
    draw_text("BY Niranjan Shrestha", COLOR_AZURE, "sofachrome", 40, 150, 1150, option_to_screen());
    fill_rectangle(COLOR_GRAY, 250, 700, 910, 320, option_to_screen());
    draw_text("<<<<GAME Status>>>> ", COLOR_YELLOW, "sofachrome", 35, 300, 710, option_to_screen());
    draw_text("-->SCORE: " + to_string(game.player.score), COLOR_LIGHT_GOLDENROD_YELLOW, "sofachrome", 35, 260, 800, option_to_screen());
    draw_text("-->FUEL %: " + to_string(game.player.fuel_pct * 100), COLOR_LIGHT_GOLDENROD_YELLOW, "sofachrome", 35, 260, 850, option_to_screen());
    draw_text("-->Health Status:  " + to_string(game.player.health_pct * 100), COLOR_LIGHT_GOLDENROD_YELLOW, "sofachrome", 35, 260, 900, option_to_screen());

    refresh_screen(60);
    draw_text("Press Space Key TO PLAY", COLOR_RED, "font", 75, 0, 450, option_to_screen());

    if (key_typed(SPACE_KEY))
    {
        game = new_game();
        game.game_state = 0;
    }
}
void game_runner()
{
    game.game_state = -1;

    // while (not quit_requested())
    do
    {
        process_events();
        if (game.game_state == -1)
        {
            start_menu(game);
        }
        else if (game.game_state == 0)
        {

            handle_input(game.player);

            update_game(game);
            draw_game(game);

            if (sprite_collision(game.villan.villan_sprite, game.player.player_sprite))
            {
                game_runner();
            }
        }

        refresh_screen(60);
    } while (!quit_requested());
}
int main()
{
    open_window("Lost In Space", 1200, 1200);
    load_sound_effect("sound2", "sound2.mp3");
    play_sound_effect("sound2");
    load_resources();
    game_runner();

    return 0;
}