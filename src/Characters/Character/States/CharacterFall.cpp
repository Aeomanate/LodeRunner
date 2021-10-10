// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include "CharacterFall.hpp"

#include <utility>
#include "Character.hpp"
#include "Field.hpp"
#include "EntityState.hpp"
#include "CharacterStateFactory.hpp"

CharacterFall::CharacterFall(
    Character* character,
    TimeMs fall_interval,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, fall_timer(animation_interval)
{
    cur_fall_sprite = {
        &Sprites::smap[entity_name + "_fall_0"],
        &Sprites::smap[entity_name + "_fall_1"],
        &Sprites::smap[entity_name + "_fall_2"],
        &Sprites::smap[entity_name + "_fall_3"],
    };
    character->SetMoveInterval(fall_interval);
    character->sprite = cur_fall_sprite;
}

std::unique_ptr<EntityState<Character>> CharacterFall::Update(Coord cur_pos) {
    if(fall_timer.IfExpiredThenStart()) {
        entity->sprite = cur_fall_sprite.CurAndNext();
    }
    
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

bool CharacterFall::IsFallState() const { return true; }
