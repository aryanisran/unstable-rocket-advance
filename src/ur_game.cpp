#include "bn_sprite_ptr.h"
#include "bn_sprites.h"
#include "bn_sprite_shape_size.h"
#include "bn_fixed.h"
#include "ur_game.h"
#include "toolbox.h"
#include "bn_random.h"


namespace ur
{
    namespace game
    {
        const int offScreenX = 200;
        const int heightBuffer = 10;
        const int enemiesInWave = 2;
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

        void set_wave_y(bn::sprite_ptr wave[], bn::random rng) {

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
    }
}