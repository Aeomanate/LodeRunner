// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include <cassert>
#include <utility>
#include "CharacterJumpDown.hpp"
#include "Player.hpp"
#include "Field.hpp"
#include "CharacterIdle.hpp"
#include "CharacterOnRope.hpp"
#include "EntityState.hpp"
#include "CharacterStateFactory.hpp"

CharacterJumpDown::CharacterJumpDown(
    Coord direction,
    Character* character,
    TimeMs fall_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
{
    character->SetMoveInterval(fall_interval);
    
    if(direction.x == 0) direction = randIntXCoord(-1, 1);
    character->SetSpriteByName(entity_name + "_jump_down_" + directionXName(direction));
}

std::unique_ptr<EntityState<Character>> CharacterJumpDown::Update(Coord cur_pos) {
    if(not entity->IsMoving()) {
        if(g_field->CellAtCoord(cur_pos)->IsContainRope()) {
            return entity->StateFactory()->MakeOnRope(randIntXCoord(-1, 1));
        }
    
        if(not entity->TryFall(cur_pos)) {
            return entity->StateFactory()->MakeIdle(randIntXCoord(-1, 1));
        }
    }
    
    return nullptr;
}

bool CharacterJumpDown::IsFallState() const { return true; }
