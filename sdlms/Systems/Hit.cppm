module;

#include "entt/entt.hpp"
#include <SDL3/SDL.h>

export module systems:hit;

import components;
import core;

export void hit_effect(AttackWarp *atkw, std::optional<SDL_FPoint> head, entt::entity ent, char type, int damage, int count = 1, SDL_FPoint *p = nullptr);

export void hit_effect(AttackWarp *atkw, Mob *mob, entt::entity ent, SDL_FPoint *p = nullptr);

export void hit_effect(AttackWarp *atkw, Npc *npc, entt::entity ent, SDL_FPoint *p = nullptr);

export void hit_effect(AttackWarp *atkw, Character *cha, entt::entity ent, SDL_FPoint *p = nullptr);
