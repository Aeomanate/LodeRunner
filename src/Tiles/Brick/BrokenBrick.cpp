// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include "BrokenBrick.hpp"
#include "Brick.hpp"


BrokenBrick::BrokenBrick(Brick* brick, TimeMs broken_duration)
: EntityState(brick, "brick")
{
    broken_timer.SetInterval(broken_duration);
}

std::unique_ptr<EntityState<Brick>> BrokenBrick::Update(Coord) {
    // Broken state
    if(not broken_timer.IsStarted()) {
        broken_timer.Start();
        return nullptr;
    }
    
    if(not broken_timer.IsExpired()) {
        return nullptr;
    } else {
        return entity->MakeRecoveringState();
    }
}