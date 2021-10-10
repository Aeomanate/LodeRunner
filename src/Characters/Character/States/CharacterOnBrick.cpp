// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include <cassert>
#include "CharacterOnBrick.hpp"
#include "Player.hpp"
#include "CharacterIdle.hpp"
#include "EntityState.hpp"
#include "CharacterStateFactory.hpp"

CharacterOnBrick::CharacterOnBrick(
    Coord direction,
    Character* character,
    TimeMs move_interval,
    TimeMs frame_delay,
    std::string character_name
)
: EntityState(character, std::move(character_name))
, cur_move_sprites(direction.x > 0 ? move_right_sprites : move_left_sprites)
, move_timer(frame_delay)
{
    if(direction.y != 0) {
        throw std::logic_error("Not be able to move on Y direction");
    }
    
    move_left_sprites = {
        &Sprites::smap[entity_name + "_move_0_left"],
        &Sprites::smap[entity_name + "_move_1_left"],
        &Sprites::smap[entity_name + "_move_2_left"],
    };
    move_right_sprites = {
        &Sprites::smap[entity_name + "_move_0_right"],
        &Sprites::smap[entity_name + "_move_1_right"],
        &Sprites::smap[entity_name + "_move_2_right"],
    };
    character->SetMoveInterval(move_interval);
    character->sprite = cur_move_sprites;
}

std::unique_ptr<EntityState<Character>> CharacterOnBrick::Update(Coord) {
    if(not entity->IsMoving()) {
        return entity->StateFactory()->MakeIdle(entity->LastDirection());
    }
    
    if(not move_timer.IsStarted()) {
        move_timer.Start();
        return nullptr;
    }
    
    if(move_timer.IfExpiredThenStart()) {
        entity->sprite = cur_move_sprites.Next();
    }
    
    return nullptr;
}
