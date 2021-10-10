// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include "CharacterIdle.hpp"

#include <utility>
#include "Player.hpp"
#include "CharacterJumpDown.hpp"
#include "Rand.hpp"
#include "Field.hpp"
#include "CharacterOnRope.hpp"
#include "CharacterStuck.hpp"
#include "EntityState.hpp"
#include "CharacterStateFactory.hpp"

CharacterIdle::CharacterIdle(
    Character* character,
    Coord direction,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, cur_view_direction(direction)
{
    entity->SetSpriteByName(entity_name + "_idle_" + directionXName(cur_view_direction));
}

std::unique_ptr<EntityState<Character>> CharacterIdle::Update(Coord cur_pos) {
    if(not entity->IsMoving()) {
        if(entity->TryFall(cur_pos)) {
            entity->ForceNextDirection({0, 1});
            return nullptr;
        }
        if(Character::IsStuckPos(cur_pos)) {
            return entity->StateFactory()->MakeStuck();
        }
    }
    
    return nullptr;
}

bool CharacterIdle::IsIdleState() const { return true; }

Coord CharacterIdle::CurViewDirection() const { return cur_view_direction; }
