#include "bn_core.h"
#include "bn_display.h"
#include "bn_sprites.h"
#include "bn_bgs_mosaic.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_regular_bg_attributes.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_math.h"
#include "toolbox.h"
#include "ur_game.h"
#include "ur_title.h"
#include "ur_game_over.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_items_space_bg.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"
#include "bn_music_items.h"


#include "bn_sprite_items_big_font.h"

int main()
{
    bn::core::init();
    bn::regular_bg_ptr space_bg = bn::regular_bg_items::space_bg.create_bg(0, 0);
    bn::sprite_font font = bn::sprite_font(bn::sprite_items::big_font);
    bn::sprite_text_generator text_generator = bn::sprite_text_generator(font);
    bn::music_items::ludum_bgm.play();
    ur::title(text_generator);
    while(true) {
        int score = 0;
        score = ur::game(space_bg, text_generator);
        ur::game_over(space_bg, text_generator, score);
        bn::core::update();
    }
    return 0;
}

