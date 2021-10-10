// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 10.08.2021.
//

#include "CharacterFireIdleRight.hpp"
#include "Character.hpp"
#include "Field.hpp"

CharacterFireIdleRight::CharacterFireIdleRight(
    Character* character,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, fire_timer(animation_interval)
{
    cur_fire_sprite = {
        &Sprites::smap[entity_name + "_fire_0_right"],
        &Sprites::smap[entity_name + "_fire_1_right"],
    };
    character->sprite = cur_fire_sprite;
}

std::unique_ptr<EntityState<Character>>
CharacterFireIdleRight::Update(Coord cur_pos) {
    if(not fire_timer.IsStarted()) {
        fire_timer.Start();
        return nullptr;
    }
    
    if(not fire_timer.IfExpiredThenStart()) {
        return nullptr;
    }else {
        entity->sprite = cur_fire_sprite.Next();
    }
    
    if(cur_fire_sprite.IsBegin()) {
        Coord pos_to_break = cur_pos + Coord{1, 1};
        Coord right_pos = cur_pos + Coord{1, 0};
        bool is_right_occupiable = g_field->CellAtCoord(right_pos)->IsOccupiable(right_pos, cur_pos);
        if(is_right_occupiable and Field::IsInField(pos_to_break)) {
            g_field->CellAtCoord(pos_to_break)->TryBreak();
        }
        return entity->StateFactory()->MakeIdle({1, 0});
    }
    
    return nullptr;
}
bool CharacterFireIdleRight::IsFiringState() const {
    return true;
}
