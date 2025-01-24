#include "Portal.h"
#include "entt/entt.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <variant>
#include "Core/Core.h"
#include "Components/Components.h"
#include "Commons/Commons.h"
#include "Resources/Wz.h"

const std::u16string pt_list[] = {u"sp", u"pi", u"pv", u"pc", u"pg", u"tp", u"ps",
                                  u"pgi", u"psi", u"pcs", u"ph", u"psh", u"pcj",
                                  u"pci", u"pcig", u"pshg"};

void load_portal(wz::Node *node, int id)
{
    const int z_index = 900000000;

    auto pt = dynamic_cast<wz::Property<int> *>(node->get_child(u"pt"))->get();

    if (!(pt < 0 || pt >= sizeof(pt_list)))
    {
        auto ent = World::registry->create();

        auto tm = dynamic_cast<wz::Property<int> *>(node->get_child(u"tm"))->get();
        auto pn = dynamic_cast<wz::Property<wz::wzstring> *>(node->get_child(u"pn"))->get();
        auto tn = dynamic_cast<wz::Property<wz::wzstring> *>(node->get_child(u"tn"))->get();

        auto x = dynamic_cast<wz::Property<int> *>(node->get_child(u"x"))->get();
        auto y = dynamic_cast<wz::Property<int> *>(node->get_child(u"y"))->get();

        if (pt == 7)
        {
            pt = 2;
        }

        auto &por = World::registry->emplace<Portal>(ent);
        por.tm = tm;
        por.pt = pt;
        por.pn = pn;
        por.tn = tn;

        World::registry->emplace<Transform>(ent, x, y, id + z_index);

        auto url = u"MapHelper.img/portal/game/" + pt_list[pt];
        if (auto portal = Wz::Map->get_root()->find_from_path(url))
        {
            if (portal->get_child(u"default") != nullptr)
            {
                // 三段式传送门
                por.a.push_back(new AnimatedSprite(portal->find_from_path(u"default/portalContinue")));
                por.a.push_back(new AnimatedSprite(portal->find_from_path(u"default/portalExit")));
                por.a.push_back(new AnimatedSprite(portal->find_from_path(u"default/portalStart")));
            }
            else
            {
                // 普通的传送门,通常为pv
                World::registry->emplace<AnimatedSprite>(ent, portal);
            }
            World::registry->emplace<Animated>(ent);
        }
    }
}

void fix_portal()
{
    std::unordered_map<std::u16string, SDL_FPoint> pors;

    auto view = World::registry->view<Portal>();
    for (auto &e : view)
    {
        auto por = &view.get<Portal>(e);
        auto tr = World::registry->try_get<Transform>(e);
        pors[por->pn] = SDL_FPoint{tr->position.x, tr->position.y};
    }
    for (auto &e : view)
    {
        auto por = &view.get<Portal>(e);
        if (por->tm == Map::id)
        {
            auto por = &view.get<Portal>(e);
            por->tn = pors[std::get<std::u16string>(por->tn)];
        }
    }
}

SDL_FPoint recent_portal(float x, float y)
{
    std::map<unsigned long, SDL_FPoint> p;

    auto view = World::registry->view<Portal>();
    for (auto &e : view)
    {
        auto por = &view.get<Portal>(e);
        if (por->pn == u"sp")
        {
            auto tr = World::registry->try_get<Transform>(e);
            auto d_x = tr->position.x - x;
            auto d_y = tr->position.y - y;
            p[d_x * d_x + d_y * d_y] = SDL_FPoint{tr->position.x, tr->position.y};
        }
    }
    if (p.begin() != p.end())
    {
        x = p.begin()->second.x;
        y = p.begin()->second.y;
    }
    return SDL_FPoint{x, y};
}
