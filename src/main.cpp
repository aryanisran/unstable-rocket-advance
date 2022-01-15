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

int main()
{
    bn::core::init();
    int enemyY;
    bn::random rng;
    enemyY = rng.get_int(1, 4);;
    enemyY = toolbox::map_int_to_range(enemyY, 1, 3, -50, 50);
    bn::fixed_point rocketVelocity;
    int randomRocketDirection = rng.get_int();
    if(randomRocketDirection != 0)
    {
        randomRocketDirection = randomRocketDirection / bn::abs(randomRocketDirection);
    }
    bn::sprite_ptr rocket = bn::sprite_items::rocket.create_sprite(-90, 0);
    bn::sprite_ptr enemy = bn::sprite_items::enemy.create_sprite(128, enemyY);
    while(true)
    {
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
        enemy.set_x(enemy.x() - 1);
        rocket.set_visible(!ur::game::checkCollision(rocket, enemy));
        bn::core::update();
    }
}
