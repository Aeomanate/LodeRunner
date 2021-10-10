// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include <iostream>
#include "BreakingBrick.hpp"
#include "Brick.hpp"

BreakingBrick::BreakingBrick(Brick* brick, TimeMs break_duration)
: EntityState(brick, "brick")
{
    cur_breaking_sprite = {
        &Sprites::smap["destroy_0"],
        &Sprites::smap["destroy_1"],
        &Sprites::smap["destroy_2"],
        &Sprites::smap["destroy_3"],
        &Sprites::smap["destroy_4"],
    };
    
    breaking_timer.SetInterval(break_duration / (TimeMs)cur_breaking_sprite.size());
    entity->sprite = cur_breaking_sprite;
}

std::unique_ptr<EntityState<Brick>> BreakingBrick::Update(Coord) {
    if(not breaking_timer.IsStarted()) {
        breaking_timer.Start();
        return nullptr;
    }
    
    if(cur_breaking_sprite.IsEnd()) {
        return entity->MakeBrokenState();
    }
    
    if(breaking_timer.IfExpiredThenStart()) {
        entity->sprite = cur_breaking_sprite.Next();
    }
    
    return nullptr;
}
