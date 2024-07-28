module;
#include "wz/Property.hpp"

export module components:animated;

import :animatedsprite;

export struct Animated
{
    int anim_index = 0;
    int anim_time = 0;
    int anim_size = 0;
    bool animate = true; // 是否播放
    int alpha = 255;     // 当前帧所对应的透明度

    AnimatedSprite *aspr = nullptr;

    char anim_step = 1;

    Animated(wz::Node *node, int alpha = 255);
    Animated(AnimatedSprite *aspr);
    Animated() = default;
};
