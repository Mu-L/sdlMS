#include "Character.h"
#include "Portal.h"

#include "entt/entt.hpp"

#include "Core/Core.h"
#include "Components/Components.h"
#include "Commons/Commons.h"
#include "Resources/Wz.h"

void load_character(float x, float y, bool sp, entt::entity ent)
{
    auto cha = &World::registry->emplace<Character>(ent);

    cha->add_head(u"00012000");
    cha->add_body(u"00002000");
    cha->add_coat(u"01040002");
    cha->add_pants(u"01061002");
    cha->add_face(u"00021001");
    cha->add_hairs(u"00031000");
    // cha->add_cap(u"01002152");
    // cha->add_shoes(u"01070002");
    // cha->add_cape(u"01102053");
    // cha->add_shield(u"01092049");
    std::u16string weapon_id = u"01472032";
    cha->add_weapon(weapon_id);
    World::registry->emplace<WeaponInfo>(ent, weapon_id);

    World::registry->emplace<Hit>(ent);
    World::registry->emplace<Attack>(ent);
    World::registry->emplace<Animated>(ent);
    World::registry->emplace<Effect>(ent);
    World::registry->emplace<Damage>(ent);
    if (sp)
    {
        World::registry->emplace<Transform>(ent, recent_portal(x, y), FRONT_BACKGROUND_Z);
    }
    else
    {
        World::registry->emplace<Transform>(ent, x, y, FRONT_BACKGROUND_Z);
    }
    World::registry->emplace<Move>(ent);
    World::zindex = true;
    return;
}