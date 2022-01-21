#ifndef UR_GAME_OVER_H_
#define UR_GAME_OVER_H_
#include "bn_sprite_ptr.h"
#include "bn_random.h"
#include "bn_bgs_mosaic.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_regular_bg_attributes.h"
#include "bn_sprite_text_generator.h"

namespace ur {
    void game_over(bn::regular_bg_ptr bg, bn::sprite_text_generator text_generator, int score);
}

#endif