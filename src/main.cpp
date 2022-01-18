#include "bn_core.h"
#include "bn_sprites.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_keypad.h"
#include "bn_sprite_items_rocket.h"
#include "bn_sprite_items_enemy.h"
#include "bn_random.h"
#include "bn_math.h"
#include "toolbox.h"
#include "ur_game.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bn_log.h"

bn::random rng;
namespace 
{
    void title() {
        //TODO: show title, show press start to start game
        while(!bn::keypad::start_pressed()) {
            
        }
    }
    void game() {
        //TODO:show score somewhere
        const int offScreenX = 200;
        int activePair = 0;
        bn::fixed_point rocketVelocity;
        int randomRocketDirection = rng.get_int(-1, 1);
        int changeDirectionTiming = rng.get_int(4, 10) * bn::timers::ticks_per_frame() * 60;
        BN_LOG("timing: ", changeDirectionTiming);
        bn::timer timer = bn::timer();
        bn::sprite_ptr rocket = bn::sprite_items::rocket.create_sprite(-90, 0);
        bn::sprite_ptr enemies[3][2] = {
            {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)},
            {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)},
            {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)}
        };
        ur::game::set_wave_y(enemies[activePair], rng);
        bool collided = false;
        while(!collided)
        {
            if(timer.elapsed_ticks() >= changeDirectionTiming) {
                changeDirectionTiming = rng.get_int(4, 10)  * bn::timers::ticks_per_frame() * 60;
                randomRocketDirection = rng.get_int(-1, 1);
                timer.restart();

            }
            if(bn::keypad::up_held())
            {
                rocketVelocity.set_y(randomRocketDirection - 2);
            }
            else if(bn::keypad::down_held())
            {
                rocketVelocity.set_y(randomRocketDirection + 2);
            }
            else
            {
                rocketVelocity.set_y(randomRocketDirection);
            }
            rocket.set_position(rocket.position() + rocketVelocity);
            ur::game::move_wave_to_player(enemies[activePair]);
            for (int i = 0; i < 2; i++)
            {
                if(ur::game::check_collision(rocket, enemies[activePair][i])) {
                    collided = true;
                }
            }
            rocket.set_visible(!collided);
            if(enemies[activePair][0].x() + enemies[activePair][0].shape_size().width() <= rocket.x()) {
                ur::game::reset_wave(enemies[activePair]);
                if(activePair >= 2) {
                    activePair = 0;
                }
                else {
                    activePair++;
                }
                ur::game::set_wave_y(enemies[activePair], rng);
            }
            bn::core::update();
        }
    }
    void game_over() {
        //TODO:show score achieved by run, show high score, press start to play again
    }
}

int main()
{
    bn::core::init();
    while(true) {
        game();
        bn::core::update();
    }
    return 0;
}

