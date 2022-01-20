#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprites.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_titlelogo.h"
#include "bn_random.h"
#include "bn_math.h"
#include "toolbox.h"
#include "ur_game.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"

namespace ur {
    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;
    constexpr bn::fixed x = 0;
    void title(bn::sprite_text_generator text_generator) {
        bn::sprite_ptr logo = bn::sprite_items::titlelogo.create_sprite(0,0);
        text_generator.set_center_alignment();
        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(x, text_y_limit, "Press START to play", text_sprites);
        bn::vector<bn::sprite_ptr, 32> char_sprites;
        text_generator.generate(x, text_y_limit - text_y_inc, "Made by Aryan", char_sprites);
        while(!bn::keypad::start_pressed()) {
            bn::core::update();
        }
    }
}