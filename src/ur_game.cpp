#include "bn_core.h"
#include "bn_sprites.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_keypad.h"
#include "bn_sprite_items_rocket.h"
#include "bn_sprite_items_enemy.h"
#include "bn_sprite_items_alert.h"
#include "bn_random.h"
#include "bn_math.h"
#include "toolbox.h"
#include "ur_game.h"
#include "ur_title.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bn_log.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_display.h"
#include <bn_string.h>

namespace ur
{
    bn::random rng;
    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    bool check_collision(bn::sprite_ptr sprite1, bn::sprite_ptr sprite2)
    {
        if(sprite1.y() + sprite1.shape_size().height() <= sprite2.y() || sprite1.y() >= sprite2.y() + sprite2.shape_size().height())
        {
            return false;
        }
        else
        {
            if(sprite1.x() + sprite1.shape_size().width() <= sprite2.x() || sprite1.x() >= sprite2.x() + sprite2.shape_size().width())
            {
                return false;
            }
            else 
            {
                return true;
            }
        }
    }

    void set_wave_y(bn::sprite_ptr wave[]) {

        int enemyY = 0;
        enemyY = rng.get_int(1, 4);
        enemyY = toolbox::map_int_to_range(enemyY, 1, 3, -50, 50);
        wave[0].set_y(enemyY);
        enemyY = rng.get_int(1, 3);
        switch (enemyY)
        {
        case -50:
            enemyY = toolbox::map_int_to_range(enemyY, 1, 2, 0, 50);
            break;
        case 0:
            enemyY = toolbox::map_int_to_range(enemyY, 1, 2, -50, 50);
            break;
        case 50:
            enemyY = toolbox::map_int_to_range(enemyY, 1, 2, -50, 0);
            break;
        default:
            enemyY = toolbox::map_int_to_range(enemyY, 1, 2, -50, 50);
            break;
        }
        wave[1].set_y(enemyY);
    }

    void move_wave_to_player(bn::sprite_ptr wave[]) {
        for (int i = 0; i < enemiesInWave; i++)
        {
            wave[i].set_x(wave[i].x() - 1);
        }
        
    }

    void reset_wave(bn::sprite_ptr wave[]) {
        for (int i = 0; i < enemiesInWave; i++)
        {
            wave[i].set_x(offScreenX);
        }
    }

    int game(bn::regular_bg_ptr bg, bn::sprite_text_generator text_generator) {
            //TODO:show score somewhere
            int activePair = 0;
            bn::fixed_point rocketVelocity;
            int randomRocketDirection = 0;
            int changeDirectionTiming = rng.get_int(4, 10) * bn::timers::ticks_per_frame() * 60;
            bn::timer timer = bn::timer();
            bn::sprite_ptr rocket = bn::sprite_items::rocket.create_sprite(-90, 0);
            bn::sprite_ptr enemies[3][2] = {
                {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)},
                {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)},
                {bn::sprite_items::enemy.create_sprite(offScreenX, 0), bn::sprite_items::enemy.create_sprite(offScreenX, 0)}
            };
            bn::fixed_point alertOffset = bn::fixed_point(10, -10);
            bn::sprite_ptr alert = bn::sprite_items::alert.create_sprite(rocket.position() + alertOffset);
            alert.set_visible(false);
            set_wave_y(enemies[activePair]);
            bool collided = false;
            int framesElapsed = 0;
            int score = 0;
            while(!collided)
            {
                if(timer.elapsed_ticks() >= changeDirectionTiming - bn::timers::ticks_per_frame() * 60) {
                    alert.set_visible(true);
                }
                if(timer.elapsed_ticks() >= changeDirectionTiming) {
                    changeDirectionTiming = rng.get_int(4, 10)  * bn::timers::ticks_per_frame() * 60;
                    randomRocketDirection = rng.get_int(-1, 2);
                    alert.set_visible(false);
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
                move_wave_to_player(enemies[activePair]);
                for (int i = 0; i < 2; i++)
                {
                    if(check_collision(rocket, enemies[activePair][i])) {
                        collided = true;
                    }
                }
                rocket.set_visible(!collided);
                if(enemies[activePair][0].x() + enemies[activePair][0].shape_size().width() <= rocket.x()) {
                    reset_wave(enemies[activePair]);
                    if(activePair >= 2) {
                        activePair = 0;
                    }
                    else {
                        activePair++;
                    }
                    set_wave_y(enemies[activePair]);
                }
                alert.set_position(rocket.position() + alertOffset);
                bg.set_x(bg.x() - 1);
                framesElapsed++;
                if(framesElapsed > 60) {
                    score++;
                    framesElapsed = 0;
                }
                bn::vector<bn::sprite_ptr, 32> text_sprites;
                text_generator.generate(0, -text_y_limit, bn::to_string<32>(score), text_sprites);
                bn::core::update();
            }
            return score;
    }
}