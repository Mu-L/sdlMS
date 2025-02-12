#pragma once

#include "Components/Components.h"
#include "entt/entt.hpp"
#include <SDL3/SDL.h>
#include <optional>

void attack_run();

void attack_iterator(AttackWarp *atkw);

void attack_mob(AttackWarp *atkw);

void attack_npc(AttackWarp *atkw);

void attack_character(AttackWarp *atkw);

void attack_reactor(AttackWarp *atkw);

bool mob_attack();

bool trap_attack();