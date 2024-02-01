#ifndef HEADER_SDLMS_EVENTSPRITE
#define HEADER_SDLMS_EVENTSPRITE

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <variant>

#include "sdlms/animatedsprite.hpp"
#include "sdlms/sprite.hpp"
#include "sdlms/dynamicsprite.hpp"

class EventSprite
{
public:
    enum Event
    {
        NORMAL,
        PRESSED,
        DISABLED,
        MOUSEOVER,
        KEYFOCUSED,
    };

    static inline const std::map<std::u16string, Event> EventMap = {
        {u"normal", NORMAL},
        {u"press", PRESSED},
        {u"disabled", DISABLED},
        {u"mouseover", MOUSEOVER},
        {u"keyfocused", KEYFOCUSED},
    };

public:
    EventSprite(std::map<Event, DynamicSprite> eventsprite);
    void draw();
    void update(int elapsedTime);

public:
    std::map<Event, DynamicSprite> _eventsprite;
};
#endif