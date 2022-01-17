#ifndef UR_GAME_H_
#define UR_GAME_H_
#include "bn_sprite_ptr.h"
#include "bn_random.h"

namespace ur
{
    namespace game
    {
        bool check_collision(bn::sprite_ptr sprite1, bn::sprite_ptr sprite2);
        void set_wave_y(bn::sprite_ptr wave[], bn::random rng);
        void move_wave_to_player(bn::sprite_ptr wave[]);
        void reset_wave(bn::sprite_ptr wave[]);
    }
}
#endif