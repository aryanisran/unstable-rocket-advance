#ifndef UR_GAME_H_
#define UR_GAME_H_
#include "bn_sprite_ptr.h"

namespace ur
{
    namespace game
    {
        bool checkCollision(bn::sprite_ptr sprite1, bn::sprite_ptr sprite2);
    }
}
#endif