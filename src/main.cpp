#include "bn_core.h"
#include "bn_sprites.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_math.h"
#include "toolbox.h"
#include "ur_game.h"
#include "ur_title.h"
#include "bn_sprite_text_generator.h"

#include "bn_sprite_items_big_font.h"

int main()
{
    bn::core::init();
    bn::sprite_font font = bn::sprite_font(bn::sprite_items::big_font);
    bn::sprite_text_generator text_generator = bn::sprite_text_generator(font);
    ur::title(text_generator);
    while(true) {
        ur::game();
        bn::core::update();
    }
    return 0;
}

