#pragma once
#include "type/type_color.h"

namespace rgp::constant {
    namespace path {
        constexpr auto PLAYER_ONE_SPRITE_PATH           = "asset/player1_sprite.png";
        constexpr auto ZEN_MARU_GOTHIC_MEDIUM_TTF_PATH  = "asset/ZenMaruGothic-Medium.ttf";
        constexpr auto PLAYER_SHOOT_WAV_PATH            = "asset/player_shoot.wav";
    }

    namespace color {
        constexpr Color BLACK_OPAQUE = {0, 0, 0, 255};
        constexpr Color WHITE_OPAQUE = {255, 255, 255, 255};
    }
}
