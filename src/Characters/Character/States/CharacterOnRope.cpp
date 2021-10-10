// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include <cassert>
#include "CharacterOnRope.hpp"
#include "Player.hpp"

CharacterOnRope::CharacterOnRope(
    Coord direction,
    Character* character,
    TimeMs move_interval,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, cur_frame(direction.x > 0 ? on_rope_right : on_rope_left)
, animation_timer(animation_interval)
{
    assert(direction.y == 0 and "Move on rope available only by x");
    on_rope_left = {
        &Sprites::smap[entity_name + "_on_rope_0_left"],
        &Sprites::smap[entity_name + "_on_rope_1_left"],
        &Sprites::smap[entity_name + "_on_rope_2_left"],
    };
    on_rope_right = {
        &Sprites::smap[entity_name + "_on_rope_0_right"],
        &Sprites::smap[entity_name + "_on_rope_1_right"],
        &Sprites::smap[entity_name + "_on_rope_2_right"],
    };
    
    character->SetMoveInterval(move_interval);
    character->sprite = cur_frame;
}

std::unique_ptr<EntityState<Character>> CharacterOnRope::Update(Coord cur_pos) {
    if(entity->IsMoving() and animation_timer.IfExpiredThenStart()) {
        entity->sprite = cur_frame.Next();
    }
    
    return nullptr;
}

bool CharacterOnRope::IsOnRopeState() const { return true; }
