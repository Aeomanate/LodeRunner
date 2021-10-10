// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 10.08.2021.
//

#include "CharacterFireLadderLeft.hpp"
#include "Character.hpp"
#include "Field.hpp"

CharacterFireLadderLeft::CharacterFireLadderLeft(
    Character* character,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, fire_timer(animation_interval)
{ }

std::unique_ptr<EntityState<Character>>
    CharacterFireLadderLeft::Update(Coord cur_pos) {
    if(not fire_timer.IsStarted()) {
        Coord pos_to_break = cur_pos + Coord{-1, 1};
        bool is_breaking = false;
        Coord left_pos = cur_pos + Coord{-1, 0};
        bool is_left_occupiable = g_field->CellAtCoord(left_pos)->IsOccupiable(left_pos, cur_pos);
        if(is_left_occupiable and Field::IsInField(pos_to_break)) {
            is_breaking = g_field->CellAtCoord(pos_to_break)->TryBreak();
        }
        if(not is_breaking) {
            return entity->StateFactory()->MakeOnLadder();
        }
        
        entity->SetSpriteByName(entity_name + "_fire_ladder_left");
        fire_timer.Start();
        return nullptr;
    }
    
    if(not fire_timer.IsExpired()) {
        return nullptr;
    }
    
    return entity->StateFactory()->MakeOnLadder();
}
bool CharacterFireLadderLeft::IsFiringState() const {
    return true;
}
