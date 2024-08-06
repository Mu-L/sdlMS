module;

#include <vector>
#include <SDL3/SDL.h>

export module components:damage;

import :sprite;

export struct Damage
{
    static inline SpriteWarp *sprs[10];
    static void init();

    struct Info
    {
        int damage;
        int alpha;
        int index;
    };

    // int alpha = 255;
    std::vector<Info> damage;
    SDL_FPoint *head;
};
