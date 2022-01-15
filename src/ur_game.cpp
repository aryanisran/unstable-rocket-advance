#ifndef UR_GAME_H_
#define UR_GAME_H_
#include "bn_sprite_ptr.h"
#include "bn_sprites.h"
#include "bn_sprite_shape_size.h"
#include "bn_fixed.h"
#include "ur_game.h"

namespace ur
{
    namespace game
    {
        const int heightBuffer = 10;
        bool checkCollision(bn::sprite_ptr sprite1, bn::sprite_ptr sprite2)
        {
            if(sprite1.y() + sprite1.shape_size().height() + heightBuffer <= sprite2.y() || sprite1.y() + heightBuffer >= sprite2.y() + sprite2.shape_size().height())
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
    }
}
#endif