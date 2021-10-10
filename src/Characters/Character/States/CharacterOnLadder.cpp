// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include "CharacterOnLadder.hpp"
#include "Player.hpp"

CharacterOnLadder::CharacterOnLadder(
    Character* character,
    TimeMs move_interval,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, animation_timer(animation_interval)
{
   
   cur_frame = {
       &Sprites::smap[entity_name + "_on_ladder_0"],
       &Sprites::smap[entity_name + "_on_ladder_1"],
       &Sprites::smap[entity_name + "_on_ladder_2"],
       &Sprites::smap[entity_name + "_on_ladder_3"],
   };
    
   character->SetMoveInterval(move_interval);
    character->sprite = cur_frame;
}

std::unique_ptr<EntityState<Character>> CharacterOnLadder::Update(Coord cur_pos) {
    if(entity->IsMoving() and animation_timer.IfExpiredThenStart()) {
        entity->sprite = cur_frame.Next();
    }
    
    return nullptr;
}

bool CharacterOnLadder::IsOnLadderState() const { return true; }
