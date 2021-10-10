// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include "CharacterStuck.hpp"
#include "Character.hpp"
#include "Field.hpp"

CharacterStuck::CharacterStuck(
    Character* character,
    TimeMs fall_interval,
    TimeMs animation_interval,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, anim_timer(animation_interval)
, max_stuck_timer(1000)
{
    cur_sprite = {
        &Sprites::smap[entity_name + "_stuck_0"],
        &Sprites::smap[entity_name + "_stuck_1"],
        &Sprites::smap[entity_name + "_stuck_2"],
        &Sprites::smap[entity_name + "_stuck_3"],
    };
    character->SetMoveInterval(fall_interval);
    character->sprite = cur_sprite;
    max_stuck_timer.Start();
}

std::unique_ptr<EntityState<Character>> CharacterStuck::Update(Coord cur_pos) {
    if(anim_timer.IfExpiredThenStart()) {
        entity->sprite = cur_sprite.CurAndNext();
    }
    
    if(not max_stuck_timer.IsExpired()) {
        return nullptr;
    }
    
    return entity->StateFactory()->MakeLose();
}

bool CharacterStuck::IsStuckState() const { return true; }
