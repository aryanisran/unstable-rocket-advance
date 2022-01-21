#include "bn_core.h"
#include "bn_sprites.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_builder.h"
#include "bn_keypad.h"
#include "bn_sprite_items_rocket.h"
#include "bn_sprite_items_enemy.h"
#include "bn_sprite_items_alert.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_display.h"
#include "bn_sound.h"
#include "bn_sound_items.h"
#include "bn_log.h"
#include "bn_string.h"
#include "bn_sstream.h"
#include "bn_sram.h"

namespace ur {
    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;
    void game_over(bn::regular_bg_ptr bg, bn::sprite_text_generator text_generator, int score) {
        bn::sound_items::ludum_playerdeath.play();
        int highScore;
        bn::sram::read(highScore);
        bg.set_position(0, 0);
        text_generator.set_center_alignment();
        bn::vector<bn::sprite_ptr, 128> text_sprites;
        bn::string<32> scoreText = "YOUR SCORE: ";
        scoreText.append(bn::to_string<5, int>(score));
        if(score > highScore) {
            scoreText.append(bn::to_string<1, char>('!'));
            highScore = score;
            bn::sram::write(highScore);
        }
        bn::string<32> highScoreText = "HIGH SCORE: ";
        highScoreText.append(bn::to_string<5, int>(highScore));
        text_generator.generate(0, -2 * text_y_inc, scoreText , text_sprites);
        text_generator.generate(0, 0, highScoreText , text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to try again", text_sprites);
        while(!bn::keypad::start_pressed()) {
            bn::core::update();
        }
    }
}