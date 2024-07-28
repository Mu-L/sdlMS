module;

#include "wz/Property.hpp"
#include <string>
#include <SDL3/SDL.h>

module components;

import :animatedsprite;
import resources;

Skill::Info::Info(wz::Node *node)
{
    // mobCount = dynamic_cast<wz::Property<int> *>(node->get_child(u"mobCount"))->get();
    // damage = dynamic_cast<wz::Property<int> *>(node->get_child(u"damage"))->get();
    // attackCount = dynamic_cast<wz::Property<int> *>(node->get_child(u"attackCount"))->get();

    if (node->get_child(u"lt"))
    {
        auto v = dynamic_cast<wz::Property<wz::WzVec2D> *>(node->get_child(u"lt"))->get();
        lt = SDL_FPoint{(float)v.x, (float)v.y};
    }
    if (node->get_child(u"rb"))
    {
        auto v = dynamic_cast<wz::Property<wz::WzVec2D> *>(node->get_child(u"rb"))->get();
        rb = SDL_FPoint{(float)v.x, (float)v.y};
    }
}

Skill::Skill(const std::u16string &id) : id(id)
{
    auto node = Wz::Skill->get_root()->find_from_path(id.substr(0, id.length() - 4) + u".img/skill/" + id);
    if (node->get_child(u"effect"))
    {
        effects.push_back(load_animatedsprite(node->get_child(u"effect")));
        for (int i = 0;; i++)
        {
            auto e = "effect" + std::to_string(i);
            if (node->get_child(e))
            {
                effects.push_back(load_animatedsprite(node->get_child(e)));
            }
            else
            {
                break;
            }
        }
    }
    if (auto hit = node->get_child(u"hit"))
    {
        hits.push_back(load_animatedsprite(hit->get_child(u"0")));
    }

    auto level = node->get_child(u"level");
    for (int i = 1; i < level->children_count() + 1; i++)
    {
        auto it = level->get_child(std::to_string(i));
        Info *info = new Info(it);
        infos.push_back(info);
    }
}

Skill *load_skill(const std::u16string &id)
{
    if (skill_cache.contains(id))
    {
        return skill_cache[id];
    }
    else
    {
        Skill *ski = new Skill(id);
        skill_cache[id] = ski;
        return ski;
    }
}
