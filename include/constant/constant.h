#pragma once
#include "type/type_color.h"

namespace rgp::constant {
    namespace path {
        constexpr auto PLAYER_ONE_SPRITE_PATH           = "asset/player1_sprite.png";
        constexpr auto PLAYER_ONE_BULLET_SPRITE_PATH    = "asset/player_bullet1.png";
        constexpr auto LEVEL_ONE_BACKGROUND_IMG_PATH    = "asset/nareko.png";
        constexpr auto ZEN_MARU_GOTHIC_MEDIUM_TTF_PATH  = "asset/ZenMaruGothic-Medium.ttf";
        constexpr auto PLAYER_SHOOT_WAV_PATH            = "asset/player_shoot.wav";
        constexpr auto MENU_MUSIC_MP3_PATH              = "asset/menu_music.mp3";
        constexpr auto LEVEL_ONE_MP3_PATH               = "asset/level1_music.mp3";
    }

    namespace color {
        constexpr Color OPAQUE          = {1, 1, 1, 255};
        constexpr Color BLACK_OPAQUE    = {0, 0, 0, 255};
        constexpr Color WHITE_OPAQUE    = {255, 255, 255, 255};

        constexpr ColorF OPAQUE_F       = {1.0f, 1.0f, 1.0f, 255.0f};
        constexpr ColorF BLACK_OPAQUE_F = {0.0f, 0.0f, 0.0f, 255.0f};
        constexpr ColorF WHITE_OPAQUE_F = {255.0f, 255.0f, 255.0f, 255.0f};
    }
}
